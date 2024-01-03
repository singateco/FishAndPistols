// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "FishingComponent.h"
#include "FishSpawner.h"
#include "PlayerCharacter.h"
#include "Revolver.h"
#include "ShotGun.h"
#include "SpadeAce.h"
#include "SunShot.h"
#include "Gun.h"
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
	//Gun = Cast<AGun>();

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


	FAttachmentTransformRules Rule = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Revolver = GetWorld()->SpawnActor<ARevolver>(RevolverClass);
	Revolver->AttachToComponent(Player->RightHandMesh, Rule, FName("Revolver_Right"));
	Revolver->SetActorHiddenInGame(true);

	SpadeAce = GetWorld()->SpawnActor<ASpadeAce>(SpadeAceClass);
	SpadeAce->AttachToComponent(Player->RightHandMesh, Rule, FName("SpadeAce_Right"));
	SpadeAce->SetActorHiddenInGame(true);

	ShotGun = GetWorld()->SpawnActor<AShotGun>(ShotGunClass);
	checkf(ShotGun, TEXT("플레이어 슈팅 컴포넌트에 샷건 안넣었음"));
	ShotGun->AttachToComponent(Player->RightHandMesh, Rule, FName("ShotGun_Right"));
	SpadeAce->SetActorHiddenInGame(true);

	SunShot = GetWorld()->SpawnActor<ASunShot>(SunShotClass);
	checkf(SunShot, TEXT("플레이어 슈팅 컴포넌트에 선샷 안넣었음"));
	SunShot->AttachToComponent(Player->RightHandMesh, Rule, FName("SunShot_Right"));
	SunShot->SetActorHiddenInGame(true);

	//왼손메시에 총 부착하는 코드
	LeftRevolver = GetWorld()->SpawnActor<ARevolver>(RevolverClass);
	LeftRevolver->AttachToComponent(Player->LeftHandMesh, Rule, FName("Revolver_Left"));
	LeftRevolver->SetActorHiddenInGame(true);

	LeftSpadeAce = GetWorld()->SpawnActor<ASpadeAce>(SpadeAceClass);
	LeftSpadeAce->AttachToComponent(Player->LeftHandMesh, Rule, FName("SpadeAce_Left"));
	LeftSpadeAce->SetActorHiddenInGame(true);

	LeftShotGun = GetWorld()->SpawnActor<AShotGun>(ShotGunClass);
	LeftShotGun->AttachToComponent(Player->LeftHandMesh, Rule, FName("ShotGun_Left"));
	LeftShotGun->SetActorHiddenInGame(true);

	LeftSunShot = GetWorld()->SpawnActor<ASunShot>(SunShotClass);
	LeftSunShot->AttachToComponent(Player->LeftHandMesh, Rule, FName("SunShot_Left"));
	LeftSunShot->SetActorHiddenInGame(true);

	UpgradeAkimbo();

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
		check(IA_LeftTriggerBool)
		check(IA_AButton)
		check(IA_BButton)

		EnhancedInput->BindAction(IA_LeftTriggerBool, ETriggerEvent::Started, this, &UShootingComponent::LeftTriggerInput_Bool);

		EnhancedInput->BindAction(IA_RightTriggerBool, ETriggerEvent::Started, this, &UShootingComponent::RightTriggerInput_Bool);

		EnhancedInput->BindAction(IA_AButton, ETriggerEvent::Started, this, &UShootingComponent::AButton);

		EnhancedInput->BindAction(IA_BButton, ETriggerEvent::Started, this, &UShootingComponent::BButton);
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


void UShootingComponent::RightTriggerInput_Bool(const FInputActionValue& value)
{
	ActionRightFire();
}

void UShootingComponent::AButton(const FInputActionValue& value)
{
	ChooseSpadeAce();
}

void UShootingComponent::BButton(const FInputActionValue& value)
{
	ChooseShotGun();
}

void UShootingComponent::ChooseRevolver()
{
	bChooseRevolver = true;
	bChooseSpadeAce = false;
	bChooseShotGun = false;
	bChooseSunShot = false;

	Revolver->SetActorHiddenInGame(false);
	SpadeAce->SetActorHiddenInGame(true);
	ShotGun->SetActorHiddenInGame(true);
	SunShot->SetActorHiddenInGame(true);

	CurrentRightGun = Revolver;

	if(IsAkimbo)
	{
		LeftRevolver->SetActorHiddenInGame(false);
		LeftSpadeAce->SetActorHiddenInGame(true);
		LeftShotGun->SetActorHiddenInGame(true);
		LeftSunShot->SetActorHiddenInGame(true);

		CurrentLeftGun = LeftRevolver;
	}
	

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
	ShotGun->SetActorHiddenInGame(true);
	SunShot->SetActorHiddenInGame(true);

	CurrentRightGun = SpadeAce;

	if (IsAkimbo)
	{
		LeftRevolver->SetActorHiddenInGame(true);
		LeftSpadeAce->SetActorHiddenInGame(false);
		LeftShotGun->SetActorHiddenInGame(true);
		LeftSunShot->SetActorHiddenInGame(true);

		CurrentLeftGun = LeftSpadeAce;
	}
}

void UShootingComponent::ChooseShotGun()
{
	bChooseRevolver = false;
	bChooseSpadeAce = false;
	bChooseShotGun = true;
	bChooseSunShot = false;

	Revolver->SetActorHiddenInGame(true);
	SpadeAce->SetActorHiddenInGame(true);
	ShotGun->SetActorHiddenInGame(false);
	SunShot->SetActorHiddenInGame(true);

	CurrentRightGun = ShotGun;

	if (IsAkimbo)
	{
		LeftRevolver->SetActorHiddenInGame(true);
		LeftSpadeAce->SetActorHiddenInGame(true);
		LeftShotGun->SetActorHiddenInGame(false);
		LeftSunShot->SetActorHiddenInGame(true);

		CurrentLeftGun = LeftShotGun;
	}

}

void UShootingComponent::ChooseSunShot()
{
	bChooseRevolver = false;
	bChooseSpadeAce = false;
	bChooseShotGun = false;
	bChooseSunShot = true;

	Revolver->SetActorHiddenInGame(true);
	SpadeAce->SetActorHiddenInGame(true);
	ShotGun->SetActorHiddenInGame(true);
	SunShot->SetActorHiddenInGame(false);

	CurrentRightGun = SunShot;

	if (IsAkimbo)
	{
		LeftRevolver->SetActorHiddenInGame(true);
		LeftSpadeAce->SetActorHiddenInGame(true);
		LeftShotGun->SetActorHiddenInGame(true);
		LeftSunShot->SetActorHiddenInGame(false);

		CurrentLeftGun = LeftSunShot;
	}
}

void UShootingComponent::UpgradeAkimbo()
{
	IsAkimbo = true;
}

void UShootingComponent::ActionLeftFire()
{
	if(IsAkimbo)
	{
		CurrentLeftGun->ActionFire();
	}
}

void UShootingComponent::ActionRightFire()
{
	CurrentRightGun->ActionFire();
}

void UShootingComponent::ReloadAllPistols()
{
	Revolver->Bullet = Revolver->MaxBullet;
	SpadeAce->Bullet = SpadeAce->MaxBullet;
	ShotGun->Bullet = ShotGun->MaxBullet;
	SunShot->Bullet = SunShot->MaxBullet;

	LeftRevolver->Bullet = LeftRevolver->MaxBullet;
	LeftSpadeAce->Bullet = LeftSpadeAce->MaxBullet;
	LeftShotGun->Bullet = LeftShotGun->MaxBullet;
	LeftSunShot->Bullet = LeftSunShot->MaxBullet;

}

void UShootingComponent::Deactivate()
{
	InputComponent->ClearBindingsForObject(this);
	Revolver->SetActorHiddenInGame(true);
	SpadeAce->SetActorHiddenInGame(true);
	ShotGun->SetActorHiddenInGame(true);
	SunShot->SetActorHiddenInGame(true);

	LeftRevolver->SetActorHiddenInGame(true);
	LeftSpadeAce->SetActorHiddenInGame(true);
	LeftShotGun->SetActorHiddenInGame(true);
	LeftSunShot->SetActorHiddenInGame(true);

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


