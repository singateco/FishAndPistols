// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeItemEntryWidget.h"

#include "Fish_GameModeBase.h"
#include "UpgradeDataObject.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UUpgradeItemEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UUpgradeDataObject* DataObject = Cast<UUpgradeDataObject>(ListItemObject);
	checkf(DataObject, TEXT("Wrong kind of data object set"))

	UpgradeImage->SetBrushFromTexture(DataObject->Data->Icon.LoadSynchronous());
	NameText->SetText(FText::FromName(DataObject->Data->Name));
	DescText->SetText(FText::FromString(DataObject->Data->Description));
	PriceText->SetText(FText::AsNumber(DataObject->Data->Price));
}

void UUpgradeItemEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameMode = GetWorld()->GetAuthGameMode<AFish_GameModeBase>();
	BuyButton->OnClicked.AddDynamic(this, &UUpgradeItemEntryWidget::BuyButtonPressed);

}

void UUpgradeItemEntryWidget::BuyButtonPressed()
{
	UUpgradeDataObject* DataObject = GetListItem<UUpgradeDataObject>();
	checkf(DataObject, TEXT("No Data Object"));

	if (GameMode->SpendGold(DataObject->Data->Price))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BuySound);

		DataObject->Data->UpgradeBought();
		Cast<UListView>(GetOwningListView())->RemoveItem(GetListItem<>());
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BlipSound);
	}
}
