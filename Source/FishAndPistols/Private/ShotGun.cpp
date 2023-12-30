// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotGun.h"
#include "Components/ArrowComponent.h"

AShotGun::AShotGun()
{
	PrimaryActorTick.bCanEverTick = true;

	BulletREF->SetupAttachment(GunMeshComponent);
	BulletREF->SetRelativeLocation(FVector(10, 0, 2));
	BulletREF->ArrowSize = 0.3f;

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshShotGun(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/shotgun/source/shotgunFinal.shotgunFinal'"));

	if (MeshShotGun.Succeeded())
	{
		GunMeshComponent->SetRelativeScale3D(FVector(2.5f));
		GunMeshComponent->SetStaticMesh(MeshShotGun.Object);
		GunMeshComponent->SetRelativeRotation(FRotator(0, 90, 0));
	}

	Bullet = 2;
}

void AShotGun::ActionFire()
{
	
}
