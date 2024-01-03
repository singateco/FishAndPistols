// Fill out your copyright notice in the Description page of Project Settings.


#include "SunShot.h"
#include "Components/ArrowComponent.h"


// Sets default values
ASunShot::ASunShot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletREF->SetupAttachment(GunMeshComponent);
	BulletREF->SetRelativeLocationAndRotation(FVector(-1050, 0, 400), FRotator(0, 0, 180));
	BulletREF->ArrowSize = 30;

	Laser->SetRelativeLocation(FVector(-522, 0, 8));

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshSunShot(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/destiny_2_-_sunshot/scene.scene'"));

	if(MeshSunShot.Succeeded())
	{
		GunMeshComponent->SetRelativeScale3D(FVector(0.02));
		GunMeshComponent->SetStaticMesh(MeshSunShot.Object);
		//GunMeshComponent->SetRelativeRotation(FRotator(0, 180, 0));
	}

	ConstructorHelpers::FObjectFinder<USoundBase> fireSound(TEXT("/Script/Engine.SoundWave'/Game/Resources/KDE/Sound/SunShotFireSound.SunShotFireSound'"));
	if (fireSound.Succeeded())
	{
		FireSound = fireSound.Object;
	}

	MaxBullet = 6;
}

// Called when the game starts or when spawned
void ASunShot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASunShot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASunShot::ActionFire()
{
	Super::ActionFire();
}

