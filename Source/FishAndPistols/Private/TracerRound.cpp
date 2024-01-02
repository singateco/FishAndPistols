// Fill out your copyright notice in the Description page of Project Settings.


#include "TracerRound.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATracerRound::ATracerRound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(4.0f);

	TracerRound = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TracerRound"));
	TracerRound->SetupAttachment(SphereCollision);
	TracerRound->SetRelativeScale3D(FVector(2.0f, 0.05f, 0.05f));

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshTracer(TEXT("/Script/Engine.StaticMesh'/Game/FishAndPistols/FP_KDE/Effect/TracerRound.TracerRound'"));

	if(MeshTracer.Succeeded())
	{
		TracerRound->SetStaticMesh(MeshTracer.Object);
	}

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));

	MovementComponent->InitialSpeed = 20000;
	MovementComponent->MaxSpeed = 20000;
	MovementComponent->Bounciness = 0;
	MovementComponent->bShouldBounce = false;
	MovementComponent->Friction = 0;
	MovementComponent->InterpLocationTime = 0.05f;
	MovementComponent->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void ATracerRound::BeginPlay()
{
	Super::BeginPlay();

	//타이머 3초뒤에 destroy();
}

// Called every frame
void ATracerRound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

