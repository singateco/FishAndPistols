// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class FISHANDPISTOLS_API UUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UListView* GunUpgradeList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UListView* GlobalUpgradeList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UListView* LureUpgradeList;
};
