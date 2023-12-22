// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Components/ActorComponent.h"
#include "ShootingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FISHANDPISTOLS_API UShootingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent) override;


	//----------------------------Variable--------------------------------
	UPROPERTY(EditAnywhere)
	bool bChoosePistol;


	//----------------------------Function--------------------------------
	
	void ActionFire();
	void PistolFire();



};
