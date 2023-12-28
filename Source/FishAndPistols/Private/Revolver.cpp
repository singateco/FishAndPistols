// Fill out your copyright notice in the Description page of Project Settings.


#include "Revolver.h"
#include "Components/ArrowComponent.h"
#include "Fish.h"
#include "PlayerCharacter.h"
#include "DynamicMesh/MeshTransforms.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARevolver::ARevolver()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Revolver = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Revolver"));
	SetRootComponent(Revolver);
	Revolver->SetRelativeScale3D(FVector(0.7));

	BulletREF = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletREF"));
	BulletREF->SetupAttachment(Revolver);
	BulletREF->SetRelativeLocationAndRotation(FVector(-22, 0, 25), FRotator(0, 180, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshRevolver(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/revolver/source/Revolver.Revolver'"));

	if(MeshRevolver.Succeeded())
	{
		Revolver->SetStaticMesh(MeshRevolver.Object);
		Revolver->SetRelativeRotation(FRotator(0, 180, 0));
	}

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

void ARevolver::ActionFire()
{
	FHitResult HitResult;
	FVector StartLoc = BulletREF->GetComponentLocation();
	FVector EndLoc = StartLoc + BulletREF->GetForwardVector() * GunRange;

	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 0.2f);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
	{
		AFish* Fish = Cast<AFish>(HitResult.GetActor());
		if (Fish)
		{
			Fish->Destroy();
			Fish->FishDeadEffect();
			DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, false, 0.3f);
		}
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, FVector(StartLoc), FRotator(0), FVector(0.03));

	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

