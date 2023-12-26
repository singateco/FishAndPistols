// Fill out your copyright notice in the Description page of Project Settings.


#include "SpadeAce.h"
#include "Fish.h"
#include "Components/ArrowComponent.h"


// Sets default values
ASpadeAce::ASpadeAce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpadeAce = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpadeAce"));
	SetRootComponent(SpadeAce);

	BulletREF = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletREF"));
	BulletREF->SetupAttachment(SpadeAce);
	BulletREF->SetRelativeLocationAndRotation(FVector(0, 23, 17), FRotator(0, 90, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshSpadeAce(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/ace-of-spades-destiny-2/source/Ace_of_Spades.Ace_of_Spades'"));

	if (MeshSpadeAce.Succeeded())
	{
		SpadeAce->SetStaticMesh(MeshSpadeAce.Object);
		SpadeAce->SetRelativeRotation(FRotator(0, -90, 0));
	}

	

}

// Called when the game starts or when spawned
void ASpadeAce::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpadeAce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


