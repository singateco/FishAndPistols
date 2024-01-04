// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "GameFramework/Actor.h"
#include "SunShot.generated.h"

UCLASS()
class FISHANDPISTOLS_API ASunShot : public AGun
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASunShot();

	//virtual void ActionFire() override;

	void Explosion();

};
