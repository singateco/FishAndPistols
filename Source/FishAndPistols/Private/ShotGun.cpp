// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotGun.h"
#include "TracerRound.h"
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

	SpreadArrow1 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpreadArrow1"));
	SpreadArrow1->SetupAttachment(GunMeshComponent);
	SpreadArrow1->ArrowSize = 0.3f;

	SpreadArrow2 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpreadArrow2"));
	SpreadArrow2->SetupAttachment(GunMeshComponent);
	SpreadArrow2->ArrowSize = 0.3f;

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

	MaxBullet = 4;
}

//샷건은 6발의 산탄을 발사
void AShotGun::ActionFire()
{
	if (Bullet >= 1)
	{
		for(int32 i=0; i<6; i++)
		{
			float X = UKismetMathLibrary::RandomFloatInRange(Spread*-1, Spread);
			float Y = UKismetMathLibrary::RandomFloatInRange(Spread*-1, Spread);
			float Z = UKismetMathLibrary::RandomFloatInRange(Spread*-1, Spread);

			FHitResult HitResult;
			FVector StartLoc = BulletREF->GetComponentLocation();
			FVector EndLoc = FVector(X, Y, Z) + StartLoc + BulletREF->GetForwardVector() * GunRange;

			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 1.5f);
			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility, Params))
			{
				AFish* Fish = Cast<AFish>(HitResult.GetActor());
				if (Fish)
				{
					Fish->TakeDamage(1);
				}
				//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, false, 0.3f);

				FRotator Rotator = HitResult.ImpactNormal.Rotation();
				UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletDecal, FVector(10, 5, 5), HitResult.ImpactPoint, Rotator, 10);

			}
		}

		Bullet--;
		BulletWidgetObject->UpdateBulletAmount(Bullet);
		GunFireEffect();
		SpawnTracerRound();
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), DryFireSound);
	}

}

void AShotGun::SpawnTracerRound()
{
	GetWorld()->SpawnActor<ATracerRound>(ATracerRound::StaticClass(), SpreadArrow1->GetComponentTransform());
	GetWorld()->SpawnActor<ATracerRound>(ATracerRound::StaticClass(), SpreadArrow2->GetComponentTransform());
}
