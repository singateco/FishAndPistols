// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotGun.h"
#include "Components/ArrowComponent.h"

AShotGun::AShotGun()
{
	PrimaryActorTick.bCanEverTick = true;

	BulletREF->SetupAttachment(GunMeshComponent);
	BulletREF->SetRelativeLocationAndRotation(FVector(0.029998, -2467727.513593, 174129.028756), FRotator(-10, -90, 0));
	BulletREF->ArrowSize = 50000;

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshShotGun(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/double-barreled_shotgun/scene.scene'"));

	if (MeshShotGun.Succeeded())
	{
		GunMeshComponent->SetRelativeScale3D(FVector(0.00001));
		GunMeshComponent->SetStaticMesh(MeshShotGun.Object);
		GunMeshComponent->SetRelativeRotation(FRotator(0, 90, 10));
	}
}

void AShotGun::ActionFire()
{
	
}
