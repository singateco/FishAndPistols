// Fill out your copyright notice in the Description page of Project Settings.


#include "SpadeAce.h"

#include "BulletAmount.h"
#include "Fish.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASpadeAce::ASpadeAce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletREF->SetupAttachment(GunMeshComponent);
	BulletREF->SetRelativeLocationAndRotation(FVector(0, 23, 21), FRotator(0, 90, 0));

	Laser->SetRelativeLocation(FVector(0, 521, 21));
	Laser->SetRelativeRotation(FRotator(0, 90, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshSpadeAce(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/ace-of-spades-destiny-2/source/Ace_of_Spades.Ace_of_Spades'"));

	if (MeshSpadeAce.Succeeded())
	{
		GunMeshComponent->SetStaticMesh(MeshSpadeAce.Object);
		//GunMeshComponent->SetRelativeRotation(FRotator(0, -90, 0));
	}

	ConstructorHelpers::FObjectFinder<USoundBase> fireSound(TEXT("/Script/Engine.SoundWave'/Game/Resources/KDE/Sound/SpadeAceFireSound.SpadeAceFireSound'"));
	if (fireSound.Succeeded())
	{
		FireSound = fireSound.Object;
	}

	MaxBullet = 6;
	
}

// Called when the game starts or when spawned
void ASpadeAce::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpadeAce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//스페이드 에이스는 2데미지
void ASpadeAce::ActionFire()
{
	if (Bullet >= 1)
	{
		FHitResult HitResult;
		FVector StartLoc = BulletREF->GetComponentLocation();
		FVector EndLoc = StartLoc + BulletREF->GetForwardVector() * GunRange;

		//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 0.2f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility, Params))
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.GetActor()->GetActorNameOrLabel());
			AFish* Fish = Cast<AFish>(HitResult.GetActor());
			if (Fish)
			{
				Fish->TakeDamage(2);
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
