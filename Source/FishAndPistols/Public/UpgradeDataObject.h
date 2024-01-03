// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeComponent.h"
#include "UObject/NoExportTypes.h"
#include "UpgradeDataObject.generated.h"

/**
 * 
 */
UCLASS()
class FISHANDPISTOLS_API UUpgradeDataObject : public UObject
{
	GENERATED_BODY()

public:
	const FUpgradeData* Data;
};
