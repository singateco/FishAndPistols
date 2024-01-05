// Fill out your copyright notice in the Description page of Project Settings.


#include "Fish.h"

#include "Fish_GameModeBase.h"
#include "GoldDropWidgetActor.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AFish::AFish()
	:
	Box(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"))),
	StaticMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"))),
	ProjectileMovementComponent(CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Box->SetBoxExtent(FVector(64));
	SetRootComponent(Box);
	StaticMeshComponent->SetupAttachment(Box);
	ProjectileMovementComponent->bAutoActivate = true;

	Box->SetCollisionObjectType(ECC_GameTraceChannel2);

	// Set lifetime.
	AActor::SetLifeSpan(15.f);

	// Set up speed.
	ProjectileMovementComponent->InitialSpeed = DefaultSpeed;
	ProjectileMovementComponent->Velocity = FVector(0, 0, 1);

	ConstructorHelpers::FObjectFinder<USoundBase> coinSound(TEXT("/Script/Engine.SoundWave'/Game/Resources/KDE/Sound/Mario-coin-sound.Mario-coin-sound'"));
	if (coinSound.Succeeded())
	{
		CoinSound = coinSound.Object;
	}

}

// Called when the game starts or when spawned
void AFish::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;
}

// Called every frame
void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("%s: %.f"), *GetActorNameOrLabel(), GetActorLocation().Z)
}


void AFish::Die()
{
	AFish_GameModeBase* GameMode = GetWorld()->GetAuthGameMode<AFish_GameModeBase>();
	GameMode->AddGold(GoldDropAmount);
	FishDeadEffect();

	AGoldDropWidgetActor* DropWidget = GetWorld()->SpawnActorDeferred<AGoldDropWidgetActor>(GoldDropWidgetActorClass, FTransform(FRotator::ZeroRotator, GetActorLocation() + FVector(-100, 0, 0)));
	DropWidget->Amount = GoldDropAmount;
	UGameplayStatics::FinishSpawningActor(DropWidget, FTransform(FRotator::ZeroRotator, GetActorLocation() + FVector(-100, 0, -45)));

	Destroy();
}

void AFish::FishDeadEffect()
{
	SetActorEnableCollision(false);

	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	NiagaraComp->SetVariableInt(TEXT("Amount"), GoldDropAmount * 7);
	NiagaraComp->SetVariableObject(TEXT("Static Mesh"), this->StaticMeshComponent->GetStaticMesh());
	UGameplayStatics::PlaySound2D(GetWorld(), CoinSound, 0.5f);
}

void AFish::TakeDamage(int32 Damage)
{
	CurrentHP -= Damage;

	if (CurrentHP <= 0)
	{
		Die();
	}
	else
	{
		// 위로 뛰어오른다.
		if (GetActorLocation().Z <= ZUpwardLimit)
		{
			ProjectileMovementComponent->AddForce(FVector::UpVector * UpwardImpulseForce);	
		}
		else
		{
			ProjectileMovementComponent->AddForce(FVector::UpVector * UpwardImpulseForce / 10);
		}
	}
}

