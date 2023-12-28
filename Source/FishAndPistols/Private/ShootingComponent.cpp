// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

#include "EnhancedInputComponent.h"
#include "FishingComponent.h"
#include "FishSpawner.h"
#include "PlayerCharacter.h"
#include "Revolver.h"
#include "SpadeAce.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UShootingComponent::UShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = false;
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

	// FishSpawner가 웨이브가 끝났다고 알려주는 것에 바인딩한다.
	AFishSpawner* Spawner = Cast<AFishSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AFishSpawner::StaticClass()));
	checkf(Spawner, TEXT("맵에 FishSpawner가 없음"))
	Spawner->OnWaveOverDelegate.AddDynamic(this, &UShootingComponent::WaveOver);

	ChooseRevolver();
	ChooseSpadeAce();
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
		if (nullptr == InputComponent)
		{
			InputComponent = EnhancedInput;
		}
		

		check(IA_RightTriggerBool)
		check(IA_RightTriggerFloat)
		check(IA_LeftTriggerFloat)
		check(IA_LeftTriggerFloat)
		check(IA_AButton)

		EnhancedInput->BindAction(IA_LeftTriggerBool, ETriggerEvent::Started, this, &UShootingComponent::LeftTriggerInput_Bool);
		
		EnhancedInput->BindAction(IA_LeftTriggerFloat, ETriggerEvent::Triggered, this, &UShootingComponent::LeftTriggerInput_Float);
		EnhancedInput->BindAction(IA_LeftTriggerFloat, ETriggerEvent::Completed, this, &UShootingComponent::LeftTriggerInput_Float);

		EnhancedInput->BindAction(IA_RightTriggerBool, ETriggerEvent::Started, this, &UShootingComponent::RightTriggerInput_Bool);
		
		EnhancedInput->BindAction(IA_RightTriggerFloat, ETriggerEvent::Triggered, this, &UShootingComponent::RightTriggerInput_Float);
		EnhancedInput->BindAction(IA_RightTriggerFloat, ETriggerEvent::Completed, this, &UShootingComponent::RightTriggerInput_Float);

		EnhancedInput->BindAction(IA_AButton, ETriggerEvent::Started, this, &UShootingComponent::AButton);
	}
}

void UShootingComponent::WaveOver()
{
	Player->FishingComponent->Activate(false);
	Deactivate();
}

void UShootingComponent::LeftTriggerInput_Bool(const FInputActionValue& value)
{
	ActionLeftFire();
}

void UShootingComponent::LeftTriggerInput_Float(const FInputActionValue& value)
{
	
}

void UShootingComponent::RightTriggerInput_Bool(const FInputActionValue& value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Semi Auto"))
	ActionRightFire();
}

void UShootingComponent::RightTriggerInput_Float(const FInputActionValue& value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Full Auto"))
	
}

void UShootingComponent::AButton(const FInputActionValue& value)
{
	
}

void UShootingComponent::ChooseRevolver()
{
	checkf(RevolverClass, TEXT("리볼버 클래스 지정안함"))
	Revolver = GetWorld()->SpawnActor<ARevolver>(RevolverClass);
	FAttachmentTransformRules Rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Revolver->AttachToComponent(Player->RightHandMesh, Rules, FName("Gun_Socket_Right"));

}

void UShootingComponent::ChooseSpadeAce()
{
	checkf(SpadeAceClass, TEXT("스페이드에이스 클래스 지정안함"))
	SpadeAce = GetWorld()->SpawnActor<ASpadeAce>(SpadeAceClass);
	FAttachmentTransformRules Rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	SpadeAce->AttachToComponent(Player->LeftHandMesh, Rules, FName("Gun_Socket_Left"));
}

void UShootingComponent::ActionLeftFire()
{
	SpadeAce->ActionFire();
}

void UShootingComponent::ActionRightFire()
{
	Revolver->ActionFire();
}

void UShootingComponent::Deactivate()
{

	InputComponent->ClearBindingsForObject(this);

	if (Revolver)
	{
		Revolver->Destroy();
	}

	if (SpadeAce)
	{
		SpadeAce->Destroy();
	}

	Super::Deactivate();
}

void UShootingComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	check(InputComponent)
	SetupPlayerInputComponent(InputComponent);

	ChooseRevolver();
	ChooseSpadeAce();
}


