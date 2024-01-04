// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeComponent.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UpgradeDataObject.h"
#include "UpgradeWidget.h"
#include "Components/ListView.h"
#include "Components/WidgetInteractionComponent.h"

// Sets default values for this component's properties
UUpgradeComponent::UUpgradeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	UpgradeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Upgrade Widget Component"));

	const ConstructorHelpers::FClassFinder<UUserWidget> UpgradeWidgetFinder{
		TEXT("Blueprint'/Game/FishAndPistols/KHO/UI/WBP_UpgradeWidget.WBP_UpgradeWidget_C'")
	};
	UpgradeWidgetClass = UpgradeWidgetFinder.Class;

	if (UpgradeWidgetClass)
	{
		UpgradeWidgetComponent->SetWidgetClass(UpgradeWidgetClass);
	}


	UpgradeWidgetComponent->SetDrawSize(FVector2D(768, 1024));

	ConstructorHelpers::FObjectFinder<UDataTable> DataTableFinder{
			TEXT("/Script/Engine.DataTable'/Game/FishAndPistols/KHO/Data/UpgradeDataTable.UpgradeDataTable'")
	};

	if (DataTableFinder.Succeeded())
	{
		UpgradeDataTable = DataTableFinder.Object;
	}
}


void UUpgradeComponent::UpgradeBought(FName UpgradeName)
{
	if (UpgradeName.IsEqual(FName("Shotgun")))
	{
		bShotgun = true;
	}
	else if (UpgradeName.IsEqual(FName("SpadeAce")))
	{
		bSpadeAce = true;
	}
	else if (UpgradeName.IsEqual(FName("SunShot")))
	{
		bSunShot = true;
	}
	else if (UpgradeName.IsEqual(FName("LaserSight")))
	{
		bLaserSight = true;
	}
	else if (UpgradeName.IsEqual(FName("DualWield")))
	{
		bDualWield = true;
	}
	else if (UpgradeName.IsEqual(FName("ExtendedAmmo")))
	{
		bExtendedAmmo = true;
	}
	else if (UpgradeName.IsEqual(FName("RareFishLure")))
	{
		bCanSpawnRareFish = true;
	}
	else if (UpgradeName.IsEqual(FName("ChestFishLure")))
	{
		bCanSpawnChestFish = true;
	}
	else if (UpgradeName.IsEqual(FName("SharkFishLure")))
	{
		bCanSpawnSharkFish = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unidentified item bought: %s"), *UpgradeName.ToString())
		return;
	}

	OnUpgradeStatusChanged.Broadcast(this);
}

void UUpgradeComponent::ToggleWidgetVisibility()
{
	if (UpgradeWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		Player->WidgetInteractionComponent->bShowDebug = true;
		UpgradeWidgetComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		UpgradeWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else if (UpgradeWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		Player->WidgetInteractionComponent->bShowDebug = false;
		UpgradeWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UpgradeWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

// Called when the game starts
void UUpgradeComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = GetOwner<APlayerCharacter>();
	check(Player)

	FAttachmentTransformRules Rules {EAttachmentRule::SnapToTarget, true};
	
	UpgradeWidgetComponent->AttachToComponent(Player->LeftHandMesh, Rules);
	UpgradeWidgetComponent->SetRelativeScale3D(FVector(0.05));
	UpgradeWidgetComponent->SetRelativeLocation(FVector(2.12, 24.31, -19.81));
	UpgradeWidgetComponent->SetRelativeRotation(FRotator(70, 95, 180));

	UUpgradeWidget* UpgradeWidgetObject = Cast<UUpgradeWidget>(UpgradeWidgetComponent->GetUserWidgetObject());
	check(UpgradeWidget);

	// Get Upgrade List.
	check(UpgradeDataTable)
		TArray<FUpgradeData*> UpgradeDataRows;
	UpgradeDataTable->GetAllRows(TEXT("Context String"), UpgradeDataRows);

	for (FUpgradeData* Row : UpgradeDataRows)
	{
		Row->OnUpgradeBought.AddDynamic(this, &UUpgradeComponent::UpgradeBought);

		UUpgradeDataObject* DataObject = NewObject<UUpgradeDataObject>(this, UUpgradeDataObject::StaticClass(), Row->Name);
		DataObject->Data = Row;
		UpgradeDataObjects.Add(DataObject);
	}

	for (UUpgradeDataObject* Buyable : UpgradeDataObjects)
	{
		switch (Buyable->Data->Type)
		{
		case EUpgradeType::Guns:
			UpgradeWidgetObject->GunUpgradeList->AddItem(Buyable);
			break;
		case EUpgradeType::Global:
			UpgradeWidgetObject->GlobalUpgradeList->AddItem(Buyable);
			break;
		case EUpgradeType::Lures:
			UpgradeWidgetObject->LureUpgradeList->AddItem(Buyable);
			break;
		default: ;
		}
	}

	UpgradeWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UpgradeWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UUpgradeComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UpgradeWidget = CreateWidget(GetWorld(), UpgradeWidgetClass);
	UpgradeWidgetComponent->SetWidget(UpgradeWidget);

	

}

void UUpgradeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpgradeWidgetComponent->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(UpgradeWidgetComponent->GetComponentLocation(), Player->CameraComponent->GetComponentLocation()));
}
