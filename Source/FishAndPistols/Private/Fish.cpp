// Fill out your copyright notice in the Description page of Project Settings.


#include "Fish.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AFish::AFish()
	:
	Box(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"))),
	StaticMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"))),
	ProjectileMovementComponent(CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(Box);
	StaticMeshComponent->SetupAttachment(Box);
	ProjectileMovementComponent->bAutoActivate = true;

}

// Called when the game starts or when spawned
void AFish::BeginPlay()
{
	Super::BeginPlay();

	// Set up the speed of the flying fish.
	ProjectileMovementComponent->InitialSpeed = FMath::RandRange(MinimumSpeed, MaximumSpeed);
}

// Called every frame
void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

