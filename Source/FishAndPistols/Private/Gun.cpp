// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Fish.h"
#include "TracerRound.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BulletAmount.h"
#include "UpgradeComponent.h"


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
	EffectREF = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EffectREF"));
	EffectREF->SetupAttachment(RootComp);
	EffectREF->bHiddenInGame = true;
	EffectREF->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	if (tempMesh.Succeeded())
	{
		EffectREF->SetRelativeScale3D(FVector(0.1));
		EffectREF->SetStaticMesh(tempMesh.Object);
	}

	Laser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laser"));
	Laser->SetRelativeScale3D(FVector(10, 0.005, 0.005));
	Laser->SetupAttachment(RootComp);
	Laser->SetHiddenInGame(true);

	BulletWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BulletWidget"));
	BulletWidget->SetupAttachment(RootComp);

	ConstructorHelpers::FClassFinder<UUserWidget> tempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FishAndPistols/FP_KDE/UI/WBP_BulletAmount.WBP_BulletAmount_C'"));
	if(tempWidget.Succeeded())
	{
		BulletWidget->SetWidgetClass(tempWidget.Class);
		BulletWidget->SetDrawSize(FVector2D(100, 40));
		BulletWidget->SetRelativeScale3D(FVector(0.1f));
	}

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

	BulletWidgetObject = Cast<UBulletAmount>(BulletWidget->GetUserWidgetObject());
	BulletWidgetObject->UpdateBulletAmount(Bullet);

	// TODO: 디버그용 지우기
	Laser->SetHiddenInGame(false);
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BulletWidgetObject->UpdateBulletAmount(Bullet);

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
				Fish->TakeDamage(1);
			}
			//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, false, 0.3f);

			FRotator Rotator = HitResult.ImpactNormal.Rotation();

			UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletDecal, FVector(10, 5, 5), HitResult.ImpactPoint, Rotator, 10);
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

void AGun::GunFireEffect()
{
	GetWorld()->SpawnActor<ATracerRound>(ATracerRound::StaticClass(), EffectREF->GetComponentTransform());

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, EffectREF, NAME_None, FVector(ForceInit), FRotator(FRotator::ZeroRotator), FVector(0.5));

	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}


void AGun::UpgradeExtendedMag(UUpgradeComponent* UpgradeComponent)
{
	if (!IsExtendedMag && UpgradeComponent->bExtendedAmmo)
	{
		IsExtendedMag = true;
		MaxBullet += 3;
	}
}

void AGun::UpgradeLaserSight(UUpgradeComponent* UpgradeComponent)
{
	if (!IsRazor && UpgradeComponent->bLaserSight)
	{
		IsRazor = true;
		Laser->SetHiddenInGame(false);
	}
}

