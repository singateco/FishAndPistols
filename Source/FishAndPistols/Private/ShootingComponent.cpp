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

	Revolver = GetWorld()->SpawnActor<ARevolver>(RevolverClass);
	FAttachmentTransformRules Rule = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Revolver->AttachToComponent(Player->RightHandMesh, Rule, FName("Revolver_Right"));
	Revolver->SetActorHiddenInGame(true);

	SpadeAce = GetWorld()->SpawnActor<ASpadeAce>(SpadeAceClass);
	SpadeAce->AttachToComponent(Player->RightHandMesh, Rule, FName("SpadeAce_Right"));
	SpadeAce->SetActorHiddenInGame(true);

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
	//ActionLeftFire();
}

void UShootingComponent::LeftTriggerInput_Float(const FInputActionValue& value)
{
	
}

void UShootingComponent::RightTriggerInput_Bool(const FInputActionValue& value)
{
	ActionRightFire();
}

void UShootingComponent::RightTriggerInput_Float(const FInputActionValue& value)
{
	
}

void UShootingComponent::AButton(const FInputActionValue& value)
{
	ChooseSpadeAce();
}

void UShootingComponent::ChooseRevolver()
{
	bChooseRevolver = true;
	bChooseSpadeAce = false;
	bChooseShotGun = false;
	bChooseSunShot = false;

	Revolver->SetActorHiddenInGame(false);
	SpadeAce->SetActorHiddenInGame(true);

	CurrentGun = Revolver;

}

//바꿀때마다 총 액터를 생성하면 스위칭 할때마다 총알 충전됨
void UShootingComponent::ChooseSpadeAce()
{
	bChooseRevolver = false;
	bChooseSpadeAce = true;
	bChooseShotGun = false;
	bChooseSunShot = false;

	Revolver->SetActorHiddenInGame(true);
	SpadeAce->SetActorHiddenInGame(false);

	CurrentGun = SpadeAce;
}

void UShootingComponent::ActionLeftFire()
{
	//왼손의 총을 가져와서 액션파이어 호출
}

void UShootingComponent::ActionRightFire()
{
	CurrentGun->ActionFire();
}

void UShootingComponent::ReloadAllPistols()
{
	Revolver->Bullet = Revolver->MaxBullet;
	SpadeAce->Bullet = SpadeAce->MaxBullet;
}

void UShootingComponent::Deactivate()
{
	InputComponent->ClearBindingsForObject(this);
	Revolver->SetActorHiddenInGame(true);
	SpadeAce->SetActorHiddenInGame(true);
	Super::Deactivate();
}

void UShootingComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	check(InputComponent)
	SetupPlayerInputComponent(InputComponent);

	ReloadAllPistols();
	ChooseRevolver();
	
}


