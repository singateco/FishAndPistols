// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "Revolver.h"
#include "SpadeAce.h"


// Sets default values for this component's properties
UShootingComponent::UShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = GetOwner<APlayerCharacter>();

	//Add enhanced Input Mapping
	check(InputMapping)
	ULocalPlayer* LocalPlayer = Player->GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem)
	if(Subsystem)
	{
		Subsystem->AddMappingContext(InputMapping, 1);
	}

	ChooseRevolver();
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
		check(IA_RightTriggerBool)
		check(IA_RightTriggerFloat)
		check(IA_LeftTriggerFloat)
		check(IA_LeftTriggerFloat)

		EnhancedInput->BindAction(IA_LeftTriggerBool, ETriggerEvent::Started, this, &UShootingComponent::RightTriggerInput_Bool);
		EnhancedInput->BindAction(IA_LeftTriggerFloat, ETriggerEvent::Triggered, this, &UShootingComponent::RightTriggerInput_Float);
		EnhancedInput->BindAction(IA_LeftTriggerFloat, ETriggerEvent::Completed, this, &UShootingComponent::RightTriggerInput_Float);

		EnhancedInput->BindAction(IA_RightTriggerBool, ETriggerEvent::Started, this, &UShootingComponent::RightTriggerInput_Bool);
		EnhancedInput->BindAction(IA_RightTriggerFloat, ETriggerEvent::Triggered, this, &UShootingComponent::RightTriggerInput_Float);
		EnhancedInput->BindAction(IA_RightTriggerFloat, ETriggerEvent::Completed, this, &UShootingComponent::RightTriggerInput_Float);
		
	}
}

void UShootingComponent::LeftTriggerInput_Bool(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Semi Auto"))
	ActionSemiAutoFire();
}

void UShootingComponent::LeftTriggerInput_Float(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Full Auto"))
	ActionFullAutoFire();
}

void UShootingComponent::RightTriggerInput_Bool(const FInputActionValue& value)
{
	
}

void UShootingComponent::RightTriggerInput_Float(const FInputActionValue& value)
{
	
}

void UShootingComponent::ChooseRevolver()
{
	bChooseRevolver = true;
	bChooseSpadeAce = false;

	Revolver = GetWorld()->SpawnActor<ARevolver>();
	FAttachmentTransformRules Rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Revolver->AttachToComponent(Player->LeftHandMesh, Rules);

}

void UShootingComponent::ChooseSpadeAce()
{
	bChooseRevolver = false;
	bChooseSpadeAce = true;

	SpadeAce = GetWorld()->SpawnActor<ASpadeAce>();
	FAttachmentTransformRules Rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	SpadeAce->AttachToComponent(Player->RightHandMesh, Rules);
}

void UShootingComponent::ActionSemiAutoFire()
{
	if(bChooseRevolver)
	{
		Revolver->ActionFire();
		UE_LOG(LogTemp, Warning, TEXT("Debug1"))
	}
	else if(bChooseSpadeAce)
	{
		SpadeAce->ActionFire();
	}
}

void UShootingComponent::ActionFullAutoFire()
{

}


