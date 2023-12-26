// Fill out your copyright notice in the Description page of Project Settings.


#include "FishSpawner.h"

#include "Fish.h"
#include "FishingComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFishSpawner::AFishSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AFishSpawner::SpawnFish()
{

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// TODO: Add variance with angles and speed
	GetWorld()->SpawnActor<AFish>(FishClass, this->GetTransform(), Params);
}

// Called when the game starts or when spawned
void AFishSpawner::BeginPlay()
{
	Super::BeginPlay();

	const APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));

	Player->FishingComponent->OnFishCaught.AddDynamic(this, &AFishSpawner::SpawnFish);
}

// Called every frame
void AFishSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

