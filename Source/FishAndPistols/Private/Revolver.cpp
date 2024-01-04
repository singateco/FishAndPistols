// Fill out your copyright notice in the Description page of Project Settings.


#include "Revolver.h"
#include "Components/ArrowComponent.h"


// Sets default values
ARevolver::ARevolver()
{

	BulletREF->SetupAttachment(GunMeshComponent);
	BulletREF->SetRelativeLocationAndRotation(FVector(-22, 0, 25), FRotator(0, 180, 0));

	Laser->SetRelativeLocation(FVector(-517, 0, 20));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRevolver(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/revolver/source/Revolver.Revolver'"));


	if (MeshRevolver.Succeeded())
	{
		GunMeshComponent->SetRelativeScale3D(FVector(0.8));
		GunMeshComponent->SetStaticMesh(MeshRevolver.Object);
		//GunMeshComponent->SetRelativeRotation(FRotator(0, 180, 0));
	}

	ConstructorHelpers::FObjectFinder<USoundBase> fireSound(TEXT("/Script/Engine.SoundWave'/Game/Resources/KDE/Sound/RevolverFireSound.RevolverFireSound'"));
	if (fireSound.Succeeded())
	{
		FireSound = fireSound.Object;
	}
	
	MaxBullet = 6;
}

// Called when the game starts or when spawned
void ARevolver::BeginPlay()
{
	Super::BeginPlay();

	//UpgradeExtendedMag();
	//UpgradeLaserSight();

}

// Called every frame
void ARevolver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


