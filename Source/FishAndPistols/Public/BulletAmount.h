// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BulletAmount.generated.h"

/**
 * 
 */
UCLASS()
class FISHANDPISTOLS_API UBulletAmount : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditInstanceOnly , meta = (BindWidget))
	class UTextBlock* BulletText;

	void UpdateBulletAmount(int Bullet);
};
