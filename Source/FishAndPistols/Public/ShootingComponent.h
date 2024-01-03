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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_LeftTriggerBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_RightTriggerBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_AButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_BButton;

	UPROPERTY()
	UEnhancedInputComponent* InputComponent;

	UPROPERTY()
	class AGun* CurrentRightGun;

	UPROPERTY()
	AGun* CurrentLeftGun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARevolver> RevolverClass;

	UPROPERTY()
	ARevolver* Revolver;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASpadeAce> SpadeAceClass;

	UPROPERTY()
	ASpadeAce* SpadeAce;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AShotGun> ShotGunClass;

	UPROPERTY()
	AShotGun* ShotGun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASunShot> SunShotClass;

	UPROPERTY()
	ASunShot* SunShot;

	UPROPERTY()
	ARevolver* LeftRevolver;

	UPROPERTY()
	ASpadeAce* LeftSpadeAce;

	UPROPERTY()
	AShotGun* LeftShotGun;

	UPROPERTY()
	ASunShot* LeftSunShot;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditAnywhere)
	bool bChooseRevolver = true;

	UPROPERTY(EditAnywhere)
	bool bChooseSpadeAce = false;

	UPROPERTY(EditAnywhere)
	bool bChooseShotGun = false;

	UPROPERTY(EditAnywhere)
	bool bChooseSunShot = false;

	UPROPERTY(EditAnywhere)
	bool IsAkimbo = false;

	//----------------------------Function--------------------------------

	UFUNCTION()
	void WaveOver();

	void LeftTriggerInput_Bool(const FInputActionValue& value);
	void RightTriggerInput_Bool(const FInputActionValue& value);
	void AButton(const FInputActionValue& value);
	void BButton(const FInputActionValue& value);

	void ChooseRevolver();
	void ChooseSpadeAce();
	void ChooseShotGun();
	void ChooseSunShot();

	void UpgradeAkimbo();

	void ActionLeftFire();
	void ActionRightFire();

	void ReloadAllPistols();

	virtual void Deactivate() override;

	virtual void Activate(bool bReset) override;
};
