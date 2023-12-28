// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "HandAnimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FISHANDPISTOLS_API UHandAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHandAnimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> InputActions);

private:
	class APlayerCharacter* Player;
	class UHandAnimInstance* HandAnim_Left;
	UHandAnimInstance* HandAnim_Right;


	void Left_Trigger_Touch(const FInputActionValue& value);
	void Left_Trigger_Value(const FInputActionValue& value);
	void Right_Trigger_Touch(const FInputActionValue& value);
	void Right_Trigger_Value(const FInputActionValue& value);


};
