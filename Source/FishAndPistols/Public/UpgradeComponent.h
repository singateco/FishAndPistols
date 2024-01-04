// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpgradeBought, FName, UpgradeName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpgradeStatusChanged, UUpgradeComponent*, UpgradeComponent);

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	Guns,
	Global,
	Lures
};

USTRUCT(BlueprintType)
struct FUpgradeData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FUpgradeBought OnUpgradeBought;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUpgradeType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;

	void UpgradeBought() const
	{
		OnUpgradeBought.Broadcast(Name);
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FISHANDPISTOLS_API UUpgradeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUpgradeComponent();

	UPROPERTY(BlueprintAssignable)
	FUpgradeStatusChanged OnUpgradeStatusChanged;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	class UWidgetComponent* UpgradeWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> UpgradeWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* UpgradeWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data", meta = (RowType = "UpgradeData"))
	UDataTable* UpgradeDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<class UUpgradeDataObject*> UpgradeDataObjects;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buyables | Global Upgrades")
	bool bLaserSight {false};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buyables | Global Upgrades")
	bool bDualWield {false};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buyables | Global Upgrades")
	bool bExtendedAmmo {false};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buyables | Guns")
	bool bShotgun {false};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buyables | Guns")
	bool bSunShot {false};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buyables | Guns")
	bool bSpadeAce {false};

	UFUNCTION()
	void UpgradeBought(FName UpgradeName);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
};
