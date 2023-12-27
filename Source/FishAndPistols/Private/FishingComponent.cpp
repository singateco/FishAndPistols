// Fill out your copyright notice in the Description page of Project Settings.


#include "FishingComponent.h"
#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "FishSpawner.h"
#include "InputMappingContext.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DateTime.h"
#include "CableActor.h"
#include "CableComponent.h"
#include "Components/BoxComponent.h"
#include "Fish.h"
#include "FishCable.h"
#include "FishHook.h"

// Sets default values for this component's properties
UFishingComponent::UFishingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;
	for (uint32 i = 0; i < DotMotionBuffer.Capacity(); i++)
	{
		DotMotionBuffer[i] = BufferIgnoreValue;
	}


}


// Called when the game starts
void UFishingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...


	OwningPlayer = GetOwner<APlayerCharacter>();


	// Add the enhanced input mapping to the player.
	check(InputMapping)
	ULocalPlayer* LocalPlayer = OwningPlayer->GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem)
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMapping, 0);
	}


	UWorld* World = GetWorld();

	// Start checking for motion value for detecting fishing motion
	World->GetTimerManager().SetTimer(MotionTimer, this, &UFishingComponent::CheckMotionValue, 0.1f, true);

	// Wait 1 second before able to detect motion
	World->GetTimerManager().SetTimer(MotionDetectedTimer, FTimerDelegate::CreateLambda(
		[&]()->void
		{
			bIsAbleToDetectMotion = true;
			MotionDetectedTimer.Invalidate();
		}
	), 1.0f, false);

	AFishSpawner* Spawner = Cast<AFishSpawner>(UGameplayStatics::GetActorOfClass(World, AFishSpawner::StaticClass()));

	checkf(Spawner, TEXT("맵에 물고기 스포너가 없음"))

	Spawner->BindWithPlayer(OwningPlayer);
}


// Called every frame
void UFishingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	const FVector RightHandLocation = OwningPlayer->RightHandMesh->GetSocketLocation(FName("middle_01_rSocket"));
	DrawDebugPoint(GetWorld(), RightHandLocation, 45, FColor::Red, false, .4f);
}

void UFishingComponent::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Set."))

		check(RightIndexTriggerInputAction)

		EnhancedInput->BindAction(RightIndexTriggerInputAction, ETriggerEvent::Started, this, &UFishingComponent::RightIndexTrigger);
		EnhancedInput->BindAction(RightIndexTriggerInputAction, ETriggerEvent::Completed, this, &UFishingComponent::RightIndexTrigger);
	}
}

void UFishingComponent::CheckMotionValue()
{
	const FVector PlayerForward = OwningPlayer->GetArrowComponent()->GetForwardVector();
	const FVector RightHandLocation = OwningPlayer->RightHandMesh->GetSocketLocation(FName("middle_01_rSocket"));

	DotMotionBuffer[BufferIndex] = PlayerForward.Dot(RightHandLocation);
	BufferIndex = DotMotionBuffer.GetNextIndex(BufferIndex);

	double min = DotMotionBuffer[0];
	double max = DotMotionBuffer[0];

	for (uint32 i = 0; i < DotMotionBuffer.Capacity(); i++)
	{
		if (DotMotionBuffer[i] == BufferIgnoreValue)
		{
			UE_LOG(LogTemp, Warning, TEXT("Motion Buffer isn't ready yet."))
			return;
		}

		if (DotMotionBuffer[i] < min)
		{
			min = DotMotionBuffer[i];
		}

		if (DotMotionBuffer[i] > max)
		{
			max = DotMotionBuffer[i];
		}
	}

	if (min - max < MotionThreshold)
	{
		MotionDetected();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Min Max Difference = %.2f"), min - max);
}

void UFishingComponent::MotionDetected()
{
	//const FDateTime Now = FDateTime::Now();
	//UE_LOG(LogTemp, Warning, TEXT("Detected, %d, %d"), Now.GetSecond(), Now.GetMillisecond());


	if (!bIsAbleToDetectMotion)
	{
		return;
	}

	bIsAbleToDetectMotion = false;

	UE_LOG(LogTemp, Warning, TEXT("Detected and accepted"));

	switch (Status)
	{
	case EFishingStatus::Idle:
		FishingStarted();
		break;
	case EFishingStatus::Fishing:
		CaughtFish();
		break;
	case EFishingStatus::Caught:
		break;
	default: ;
	}

	// Reset Motion timer cooldown.
	if (!MotionDetectedTimer.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(MotionDetectedTimer, FTimerDelegate::CreateLambda(
			[&]()->void
			{
				bIsAbleToDetectMotion = true;
				MotionDetectedTimer.Invalidate();
			}
		), MotionTimerCooldownSeconds, false);
	}
}

void UFishingComponent::MakeFishHook()
{
	
	if (!Cable)
	{
		// Make Hook
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		check(HookClass)
		AFishHook* Hook = GetWorld()->SpawnActor<AFishHook>(HookClass, OwningPlayer->FishingRodMeshComponent->GetSocketLocation(FName("LineEnd")), FRotator(90, 0, 0), Params);

		check(CableActorClass)
		Cable = GetWorld()->SpawnActorDeferred<AFishCable>(CableActorClass, OwningPlayer->FishingRodMeshComponent->GetSocketTransform(FName("LineEnd"), RTS_ParentBoneSpace), OwningPlayer, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Cable->AttachToComponent(OwningPlayer->FishingRodMeshComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("LineEnd"));
		Cable->SetActorRelativeLocation(FVector(0, 0, 0));

		// Attach the hook to cable
		Cable->CableComponent->SetAttachEndToComponent(Hook->BoxComp);
		// Make Cable visible
		Cable->CableComponent->SetVisibility(true);

		UGameplayStatics::FinishSpawningActor(Cable, FTransform(OwningPlayer->FishingRodMeshComponent->GetSocketLocation(FName("LineEnd"))));
	}

}

void UFishingComponent::RightIndexTrigger(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Triggered"))
		MakeFishHook();
		//OnFishCaught.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger Completed"))
	}
}

void UFishingComponent::FishingStarted()
{
	Status = EFishingStatus::Fishing;
	UE_LOG(LogTemp, Warning, TEXT("Fishing Started"))

	MakeFishHook();
}

void UFishingComponent::CaughtFish()
{
	Status = EFishingStatus::Caught;
	OnFishCaught.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Fish Caught"))

	Status = EFishingStatus::Idle;
}

void UFishingComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

