// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Fish_GameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGoldAmountChanged, int32, ChangedGold);

/**
 * 
 */
UCLASS()
class FISHANDPISTOLS_API AFish_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	// =============== PROPERTIES ==================

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Gold {0};

	UPROPERTY(BlueprintAssignable)
	FGoldAmountChanged OnGoldAmountChanged;

	// ================ FUNCTIONS ==================

	UFUNCTION(BlueprintCallable)
	void AddGold(int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool SpendGold(int32 Amount);
};
