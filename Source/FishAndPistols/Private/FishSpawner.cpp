// Fill out your copyright notice in the Description page of Project Settings.


#include "FishSpawner.h"

#include "Fish.h"
#include "FishingComponent.h"
#include "PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFishSpawner::AFishSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AFishSpawner::BindWithPlayer(APlayerCharacter* Player)
{
	Player->FishingComponent->OnFishCaught.AddDynamic(this, &AFishSpawner::SpawnMultipleFish);
}

void AFishSpawner::SpawnFish()
{
	// Add variance to spawner angle
	float AngleVariance = FMath::RandRange(-15, 15);
	this->SetActorRotation(GetActorRotation() + FRotator(0, AngleVariance, 0));

	// Add variance with the angles to fish themselves
	FRotator Rotator = this->GetActorRotation();
	Rotator.Yaw += FMath::RandRange(-20, 20);
	Rotator.Roll += FMath::RandRange(-20, 20);

	FTransform SpawnTransform = FTransform(Rotator, GetActorLocation());

	AFish* SpawnedFish = GetWorld()->SpawnActorDeferred<AFish>(FishClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// Add variance with the speed
	SpawnedFish->ProjectileMovementComponent->InitialSpeed = SpawnedFish->DefaultSpeed += FMath::RandRange(200, -200);
	UGameplayStatics::FinishSpawningActor(SpawnedFish, SpawnTransform);

	// Reset the spawner angle
	this->SetActorRotation(GetActorRotation() + FRotator(0, -1 * AngleVariance, 0));
}

void AFishSpawner::SlowdownTime()
{
	FTimerHandle SlowDownTimer;
	FTimerHandle FastBackDownTimer;

	// Slow down time.
	GetWorld()->GetTimerManager().SetTimer(
		SlowDownTimer,
		FTimerDelegate::CreateLambda(
			[&]()->void
			{
				GetWorldSettings()->SetTimeDilation(SlowMotionTimeScale);
			}
		),
		SlowDownStartSecond,
		false
	);


	// Set speed to normal.
	GetWorld()->GetTimerManager().SetTimer(
		FastBackDownTimer,
		FTimerDelegate::CreateLambda(
			[&]()->void
			{
				GetWorldSettings()->SetTimeDilation(1.0f);
			}
		),
		SlowDownEndSecond,
		false
	);

}

void AFishSpawner::SpawnMultipleFish()
{
	SlowdownTime();
	for (int i = 0; i < AmountToSpawn; i++)
	{
		SpawnFish();
	}

	// Start Wave over timer.
	GetWorld()->GetTimerManager().SetTimer(
			WaveTimerHandle,
			FTimerDelegate::CreateLambda(
			[&]
			{
				OnWaveOverDelegate.Broadcast();
			}),
			WaveOverSecond,
			false
	);
}

// Called when the game starts or when spawned
void AFishSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFishSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

