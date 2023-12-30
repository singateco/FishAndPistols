// Fill out your copyright notice in the Description page of Project Settings.


#include "Fish.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AFish::AFish()
	:
	Box(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"))),
	StaticMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"))),
	ProjectileMovementComponent(CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Box->SetBoxExtent(FVector(64));
	SetRootComponent(Box);
	StaticMeshComponent->SetupAttachment(Box);
	ProjectileMovementComponent->bAutoActivate = true;


	// Set lifetime.
	AActor::SetLifeSpan(15.f);

	// Set up speed.
	ProjectileMovementComponent->InitialSpeed = DefaultSpeed;
	ProjectileMovementComponent->Velocity = FVector(0, 0, 1);
}

// Called when the game starts or when spawned
void AFish::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFish::FishDeadEffect()
{
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation(), FRotator(0), FVector(1));
	check(ExplosionEffect)
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	UGameplayStatics::PlaySound2D(GetWorld(), CoinSound, 0.5f);
}

