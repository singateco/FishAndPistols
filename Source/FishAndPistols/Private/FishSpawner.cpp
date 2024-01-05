// Fill out your copyright notice in the Description page of Project Settings.


#include "FishSpawner.h"

#include "Fish.h"
#include "FishingComponent.h"
#include "PlayerCharacter.h"
#include "UpgradeComponent.h"
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
	Player->UpgradeComponent->OnUpgradeStatusChanged.AddDynamic(this, &AFishSpawner::UpgradeBought);
}

void AFishSpawner::SpawnFish(TSubclassOf<AFish> InClass)
{
	// Add variance to spawner angle
	float AngleVariance = FMath::RandRange(-20, 20);
	FRotator Variance = FRotator(0, 0, AngleVariance);

	this->SetActorRotation(GetActorRotation() + Variance);

	// Add variance with the angles to fish themselves
	FRotator Rotator = this->GetActorRotation();
	Rotator.Yaw += FMath::RandRange(-20, 20);
	Rotator.Roll += FMath::RandRange(-20, 20);
	//Rotator.Pitch += FMath::RandRange(-15, 15);


	FTransform SpawnTransform = FTransform(Rotator, GetActorLocation());

	AFish* SpawnedFish = GetWorld()->SpawnActorDeferred<AFish>(InClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// Add variance with the speed
	SpawnedFish->ProjectileMovementComponent->InitialSpeed = SpawnedFish->DefaultSpeed += FMath::RandRange(200, -200);
	UGameplayStatics::FinishSpawningActor(SpawnedFish, SpawnTransform);

	SpawnedFishes.AddUnique(SpawnedFish);
	SpawnedFish->OnEndPlay.AddDynamic(this, &AFishSpawner::FishDestroyed);

	// Reset the spawner angle
	this->SetActorRotation(GetActorRotation() - Variance);
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
	for (int i = 0; i < FMath::RandRange(AmountToSpawnMin, AmountToSpawnMax); i++)
	{
		if (bCanSpawnSharkFish && !SpawnedSharkFish)
		{
			SpawnFish(SharkClass);
			SpawnedSharkFish = true;
		}
		else if (bCanSpawnChestFish && !SpawnedChestFish)
		{
			SpawnFish(ChestFishClass);
			SpawnedChestFish = true;
		}
		else if (bCanSpawnRareFish && FMath::FRand() <= 0.5)
		{
			SpawnFish(RareFishClass);
		}
		else
		{
			SpawnFish(FishClass);
		}
	}

	// Start Wave over timer.
	/*GetWorld()->GetTimerManager().SetTimer(
			WaveTimerHandle,
			FTimerDelegate::CreateLambda(
			[&]
			{
				OnWaveOverDelegate.Broadcast();
			}),
			WaveOverSecond,
			false
	);*/

	SpawnedSharkFish = false;
	SpawnedChestFish = false;
}

void AFishSpawner::UpgradeBought(UUpgradeComponent* UpgradeComponent)
{
	this->bCanSpawnRareFish = UpgradeComponent->bCanSpawnRareFish;
	this->bCanSpawnChestFish = UpgradeComponent->bCanSpawnChestFish;
	this->bCanSpawnSharkFish = UpgradeComponent->bCanSpawnSharkFish;
}

void AFishSpawner::FishDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	SpawnedFishes.Remove(Cast<AFish>(Actor));

	if (SpawnedFishes.IsEmpty())
	{
		OnWaveOverDelegate.Broadcast();
	}
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

