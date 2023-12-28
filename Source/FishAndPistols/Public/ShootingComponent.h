// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "InputAction.h"

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

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	//----------------------------Variable--------------------------------

	UPROPERTY()
	class APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere)
	bool bChooseSemiAuto;

	UPROPERTY(EditAnywhere)
	bool bChooseFullAuto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_LeftTriggerBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_LeftTriggerFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_RightTriggerBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_RightTriggerFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_AButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARevolver> RevolverClass;

	UPROPERTY()
	ARevolver* Revolver;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASpadeAce> SpadeAceClass;

	UPROPERTY()
	ASpadeAce* SpadeAce;

	UPROPERTY()
	UEnhancedInputComponent* InputComponent;

	//----------------------------Function--------------------------------

	UFUNCTION()
	void WaveOver();

	void LeftTriggerInput_Bool(const FInputActionValue& value);
	void LeftTriggerInput_Float(const FInputActionValue& value);
	void RightTriggerInput_Bool(const FInputActionValue& value);
	void RightTriggerInput_Float(const FInputActionValue& value);

	void AButton(const FInputActionValue& value);

	void ChooseRevolver();
	void ChooseSpadeAce();

	void ActionLeftFire();
	void ActionRightFire();

	virtual void Deactivate() override;

	virtual void Activate(bool bReset) override;
};
