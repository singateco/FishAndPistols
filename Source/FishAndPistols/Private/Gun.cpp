// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Fish.h"
#include "TracerRound.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	GunMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMeshComponent"));
	SetRootComponent(RootComp);

	GunMeshComponent->SetupAttachment(RootComp);
	BulletREF = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletREF"));

	Laser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laser"));
	Laser->SetRelativeScale3D(FVector(10, 0.01, 0.01));
	Laser->SetupAttachment(RootComp);
	Laser->SetHiddenInGame(true);
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> LaserMeshFinder(TEXT("/Script/Engine.StaticMesh'/Game/FishAndPistols/FP_KDE/Effect/LaserCube.LaserCube'"));

	if(LaserMeshFinder.Succeeded())
	{
		Laser->SetStaticMesh(LaserMeshFinder.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> bulletDecal(TEXT("/Script/Engine.Material'/Game/FishAndPistols/FP_KDE/Effect/M_BulletDecal.M_BulletDecal'"));
	if(bulletDecal.Succeeded())
	{
		BulletDecal = bulletDecal.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> dryFireSound(TEXT("/Script/Engine.SoundWave'/Game/Resources/KDE/Sound/DryFireSound.DryFireSound'"));
	if(dryFireSound.Succeeded())
	{
		DryFireSound = dryFireSound.Object;
	}

	/*ConstructorHelpers::FObjectFinder<UParticleSystem> muzzleFlash(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (muzzleFlash.Succeeded())
	{
		MuzzleFlash = muzzleFlash.Object;
	}*/


}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	Bullet = MaxBullet;

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGun::ActionFire()
{
	if(Bullet >= 1)
	{
		FHitResult HitResult;
		FVector StartLoc = BulletREF->GetComponentLocation();
		FVector EndLoc = StartLoc + BulletREF->GetForwardVector() * GunRange;

		//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 0.2f);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
		{
			AFish* Fish = Cast<AFish>(HitResult.GetActor());
			if (Fish)
			{
				Fish->Die();
			}
			//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, false, 0.3f);

			/*UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletDecal, FVector(10, 5, 5), HitResult.ImpactPoint, FRotator(-90, 0, 0), 5);*/
		}
		Bullet--;
		
		GunFireEffect();
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), DryFireSound);
	}
	
}

void AGun::GunFireEffect()
{
	GetWorld()->SpawnActor<ATracerRound>(ATracerRound::StaticClass(), BulletREF->GetComponentTransform());

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, BulletREF, NAME_None, FVector(ForceInit), FRotator(FRotator::ZeroRotator), FVector(0.05));

	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

void AGun::UpgradeExtendedMag()
{
	IsExtendedMag = true;
	MaxBullet += 3;
}

void AGun::UpgradeLaserSight()
{
	IsRazor = true;
	Laser->SetHiddenInGame(false);
}

