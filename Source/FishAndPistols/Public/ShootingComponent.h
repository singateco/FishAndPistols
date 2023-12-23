// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputLibrary.h"
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

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);


	//----------------------------Variable--------------------------------
	UPROPERTY(EditAnywhere)
	bool bChoosePistol;

	UPROPERTY(EditAnywhere)
	bool bChooseSpadeAce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_RightTriggerBool;



	//----------------------------Function--------------------------------

	void RightTriggerInput_Bool(const FInputActionValue& value);
	void ActionFire();
	void PistolFire();
	void SpadeAceFire();



};
