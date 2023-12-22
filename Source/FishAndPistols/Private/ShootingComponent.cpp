// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingComponent.h"

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

	// ...
	
}


// Called every frame
void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

<<<<<<< HEAD

void UShootingComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}


void UShootingComponent::RightTriggerInput_Bool(const FInputActionValue& value)
{

}
=======
<<<<<<< HEAD
//void UShootingComponent::SetupPlayerInput(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInput(PlayerInputComponent);
//}
=======
void UShootingComponent::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInput(PlayerInputComponent);
}
>>>>>>> ff4dc70e2e5e4c6757d1922287ee442b88798a60
>>>>>>> 9e9f391635acece0845878b740609d14ac44eaba

void UShootingComponent::ActionFire()
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

void UShootingComponent::PistolFire()
{

}

void UShootingComponent::SpadeAceFire()
{

}

