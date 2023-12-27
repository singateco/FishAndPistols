// Fill out your copyright notice in the Description page of Project Settings.


#include "SunShot.h"

#include "Fish.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASunShot::ASunShot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SunShot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SunShot"));
	SetRootComponent(SunShot);
	SunShot->SetRelativeScale3D(FVector(0.02));

	BulletREF = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletREF"));
	BulletREF->SetupAttachment(SunShot);
	BulletREF->SetRelativeLocationAndRotation(FVector(-1050, 0, 400), FRotator(0, 0, 180));
	BulletREF->ArrowSize = 30;

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshSunShot(TEXT("/Script/Engine.StaticMesh'/Game/Resources/KDE/destiny_2_-_sunshot/scene.scene'"));

	if(MeshSunShot.Succeeded())
	{
		SunShot->SetStaticMesh(MeshSunShot.Object);
		SunShot->SetRelativeRotation(FRotator(0, 180, 0));
	}
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
	FHitResult HitResult;
	FVector StartLoc = BulletREF->GetComponentLocation();
	FVector EndLoc = StartLoc + BulletREF->GetForwardVector() * GunRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility))
	{
		DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 5.0f);

		AFish* Fish = Cast<AFish>(HitResult.GetActor());
		if (Fish)
		{
			Fish->Destroy();
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, FVector(StartLoc), FRotator(0), FVector(0.1));

	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

