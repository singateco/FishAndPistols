// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoldDropUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class FISHANDPISTOLS_API UGoldDropUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* GoldText;
};
