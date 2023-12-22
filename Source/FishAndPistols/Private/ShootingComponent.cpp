// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingComponent.h"

#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UShootingComponent::UShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	//Me = Cast<APlayerCharacter>(GetOwner());
	
}


// Called every frame
void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UShootingComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(IA_RightTriggerBool, ETriggerEvent::Started, this, &UShootingComponent::RightTriggerInput_Bool);
		EnhancedInput->BindAction(IA_RightTriggerBool, ETriggerEvent::Triggered, this, &UShootingComponent::RightTriggerInput_Float);
		EnhancedInput->BindAction(IA_RightTriggerBool, ETriggerEvent::Completed, this, &UShootingComponent::RightTriggerInput_Float);
		
	}
}

void UShootingComponent::RightTriggerInput_Bool(const FInputActionValue& value)
{
	ActionSemiAutoFire();
}

void UShootingComponent::RightTriggerInput_Float(const FInputActionValue& value)
{
	ActionFullAutoFire();
}

void UShootingComponent::ActionSemiAutoFire()
{
	if(bChoosePistol)
	{
		PistolFire();
	}
	else if(bChooseSpadeAce)
	{
		SpadeAceFire();
	}
}
//겟오너로 플레이어 저장하고, 총 컴포넌트의 머즐 위치정보 여기서 라인트레이스 시작
void UShootingComponent::PistolFire()
{
	
}

void UShootingComponent::SpadeAceFire()
{

}

void UShootingComponent::ActionFullAutoFire()
{

}
