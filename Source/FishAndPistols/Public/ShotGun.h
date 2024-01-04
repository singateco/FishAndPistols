// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "ShotGun.generated.h"

/**
 * 
 */
UCLASS()
class FISHANDPISTOLS_API AShotGun : public AGun
{
	GENERATED_BODY()


public:
	AShotGun();


private:
	UPROPERTY(EditAnywhere)
	float Spread = 100.0f;

	void ActionFire() override;
};
