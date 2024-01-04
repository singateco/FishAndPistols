// Fill out your copyright notice in the Description page of Project Settings.


#include "SunShot.h"

#include "BulletAmount.h"
#include "Fish.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"


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

	MaxBullet = 4;
}

//void ASunShot::ActionFire()
//{
//	if (Bullet >= 1)
//	{
//		FHitResult HitResult;
//		FVector StartLoc = BulletREF->GetComponentLocation();
//		FVector EndLoc = StartLoc + BulletREF->GetForwardVector() * GunRange*10;
//
//		DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 0.2f);
//
//		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
//		{
//			AFish* Fish = Cast<AFish>(HitResult.GetActor());
//			if (Fish)
//			{
//				Fish->Die();
//			}
//			DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, false, 0.3f);
//
//			FRotator Rotator = HitResult.ImpactNormal.Rotation();
//
//			UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletDecal, FVector(10, 5, 5), HitResult.ImpactPoint, Rotator, 10);
//		}
//
//		Bullet--;
//		BulletWidgetObject->UpdateBulletAmount(Bullet);
//		GunFireEffect();
//	}
//	else
//	{
//		UGameplayStatics::PlaySound2D(GetWorld(), DryFireSound);
//	}
//}

void ASunShot::Explosion()
{
	//UKismetSystemLibrary::SphereOverlapActors()
}

