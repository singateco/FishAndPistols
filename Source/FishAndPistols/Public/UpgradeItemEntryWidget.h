// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeItemEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class FISHANDPISTOLS_API UUpgradeItemEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* UpgradeImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DescText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PriceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BuyButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* BuySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* BlipSound;

	UPROPERTY()
	class AFish_GameModeBase* GameMode;

	UFUNCTION()
	void BuyButtonPressed();
};
