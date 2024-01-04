// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotGun.h"

#include "BulletAmount.h"
#include "Fish.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AShotGun::AShotGun()
{
	PrimaryActorTick.bCanEverTick = true;

	BulletREF->SetupAttachment(GunMeshComponent);
	BulletREF->SetRelativeLocation(FVector(10, 0, 2.8));
	BulletREF->ArrowSize = 0.3f;

	Laser->SetRelativeLocation(FVector(524, 0, 7));


	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshShotGun(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/shotgun/source/shotgunFinal.shotgunFinal'"));

	if (MeshShotGun.Succeeded())
	{
		GunMeshComponent->SetRelativeScale3D(FVector(2.5f));
		GunMeshComponent->SetStaticMesh(MeshShotGun.Object);
		//GunMeshComponent->SetRelativeRotation(FRotator(0, 90, 0));
	}

	ConstructorHelpers::FObjectFinder<USoundBase> fireSound(TEXT("/Script/Engine.SoundWave'/Game/Resources/KDE/Sound/ShotGunFireSound.ShotGunFireSound'"));
	if (fireSound.Succeeded())
	{
		FireSound = fireSound.Object;
	}

	MaxBullet = 2;
}

void AShotGun::ActionFire()
{
	if (Bullet >= 1)
	{
		for(int32 i=0; i<12; i++)
		{

			float X = UKismetMathLibrary::RandomFloatInRange(Spread*0.1, Spread);
			float Y = UKismetMathLibrary::RandomFloatInRange(Spread*0.1, Spread);
			float Z = UKismetMathLibrary::RandomFloatInRange(Spread*0.1, Spread);

			FHitResult HitResult;
			FVector StartLoc = BulletREF->GetComponentLocation();
			FVector EndLoc = FVector(X, Y, Z) + StartLoc + BulletREF->GetForwardVector() * 200;

			DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 0.2f);
			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
			{
				AFish* Fish = Cast<AFish>(HitResult.GetActor());
				if (Fish)
				{
					Fish->Die();
				}
				//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, false, 0.3f);

				FRotator Rotator = HitResult.ImpactNormal.Rotation();

				UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletDecal, FVector(10, 5, 5), HitResult.ImpactPoint, Rotator, 10);
			}
		}

		Bullet--;
		BulletWidgetObject->UpdateBulletAmount(Bullet);
		GunFireEffect();
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), DryFireSound);
	}

}
