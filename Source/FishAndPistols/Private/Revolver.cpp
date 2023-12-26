// Fill out your copyright notice in the Description page of Project Settings.


#include "Revolver.h"

#include "Components/BoxComponent.h"

// Sets default values
ARevolver::ARevolver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Revolver = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Revolver"));
	Revolver->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshRevolver(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/revolver/source/Revolver.Revolver'"));

	if(MeshRevolver.Succeeded())
	{
		Revolver->SetStaticMesh(MeshRevolver.Object);
		Revolver->SetRelativeRotation(FRotator(0, 180, 0));
	}

	BulletREF = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletREF"));
	BulletREF->SetupAttachment(Revolver);
	BulletREF->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BulletREF->SetRelativeLocationAndRotation(FVector(-24, 0, 22), FRotator(0, -180, 0));
	BulletREF->SetRelativeScale3D(FVector(0.1));
	BulletREF->bHiddenInGame = true;

}

// Called when the game starts or when spawned
void ARevolver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARevolver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

