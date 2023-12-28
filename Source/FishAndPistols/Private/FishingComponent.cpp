// Fill out your copyright notice in the Description page of Project Settings.


#include "FishingComponent.h"

#include "CableComponent.h"
#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "FishSpawner.h"
#include "InputMappingContext.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DateTime.h"
#include "FishHook.h"
#include "ShootingComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values for this component's properties
UFishingComponent::UFishingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bAutoActivate = false;
	//bWantsInitializeComponent = true;
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

	StartCheckingMotionValue();

	// Wait 1 second before able to detect motion
	World->GetTimerManager().SetTimer(MotionDetectedTimer, FTimerDelegate::CreateLambda(
		[&]()->void
		{
			bIsAbleToDetectMotion = true;
			MotionDetectedTimer.Invalidate();
		}
	), 2.0f, false);

	AFishSpawner* Spawner = Cast<AFishSpawner>(UGameplayStatics::GetActorOfClass(World, AFishSpawner::StaticClass()));

	checkf(Spawner, TEXT("맵에 물고기 스포너가 없음"))

	Spawner->BindWithPlayer(OwningPlayer);
}


// Called every frame
void UFishingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// const FVector RightHandLocation = OwningPlayer->RightHandMesh->GetSocketLocation(FName("middle_01_rSocket"));
	//DrawDebugPoint(GetWorld(), RightHandLocation, 45, FColor::Red, false, .4f);
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

	DrawDebugPoint(GetWorld(), RightHandLocation, 25.f, FColor::Cyan, false, .2f);

	DotMotionBuffer[BufferIndex] = PlayerForward.Dot(RightHandLocation);

	//UE_LOG(LogTemp, Warning, TEXT("%.1f"), DotMotionBuffer[BufferIndex]);
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
		const uint32 PrevIndex = (int32)BufferIndex - 1 < 0 ? DotMotionBuffer.Capacity() - 1 : BufferIndex - 1;
		const bool bBackward = DotMotionBuffer[PrevIndex] < DotMotionBuffer[BufferIndex];

		MotionDetected(bBackward);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Min Max Difference = %.2f"), min - max);
}

void UFishingComponent::MotionDetected(bool bBackward)
{
	//const FDateTime Now = FDateTime::Now();
	//UE_LOG(LogTemp, Warning, TEXT("Detected, %d, %d"), Now.GetSecond(), Now.GetMillisecond());




	if (!bIsAbleToDetectMotion)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Motion Detected"));

	switch (Status)
	{
	case EFishingStatus::Idle:
		if (!bBackward)
		{
			UE_LOG(LogTemp, Warning, TEXT("Motion Detected And Accepted"));
			bIsAbleToDetectMotion = false;
			FishingStarted();
		}
		break;
	case EFishingStatus::Fishing:
		if (bBackward)
		{
			UE_LOG(LogTemp, Warning, TEXT("Motion Detected And Accepted"));
			bIsAbleToDetectMotion = false;
			CaughtFish();
		}
		break;
	default: ;
	}

	// Reset Motion timer cooldown.
	if (!MotionDetectedTimer.IsValid() && !bIsAbleToDetectMotion)
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
	// Make Hook
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	check(HookClass)
	Hook = GetWorld()->SpawnActor<AFishHook>(HookClass, OwningPlayer->FishingRodMeshComponent->GetSocketLocation(FName("LineEnd")), FRotator(90, 0, 0), Params);

	const FVector ImpulseDir = OwningPlayer->GetActorForwardVector() + OwningPlayer->GetActorUpVector();
	Hook->BoxComp->AddImpulse(ImpulseDir * HookThrowSpeed);

	OwningPlayer->FishCable->SetVisibility(true);
	OwningPlayer->FishCable->SetAttachEndToComponent(Hook->MeshComp, FName("HoleSocket"));
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
	Status = EFishingStatus::Idle;
	OnFishCaught.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Fish Caught"))

	OwningPlayer->ShootingComponent->Activate(false);
	Deactivate();

	/*OwningPlayer->FishCable->SetVisibility(false);
	Hook->Destroy();
	OwningPlayer->FishingRodMeshComponent->SetVisibility(false);*/
}

// Start checking for motion value for detecting fishing motion
void UFishingComponent::StartCheckingMotionValue()
{
	GetWorld()->GetTimerManager().SetTimer(MotionTimer, this, &UFishingComponent::CheckMotionValue, 0.1f, true);
}

void UFishingComponent::Deactivate()
{
	OwningPlayer->FishCable->SetVisibility(false);

	if (Hook)
	{
		Hook->Destroy();
	}
	
	OwningPlayer->FishingRodMeshComponent->SetVisibility(false);
	OwningPlayer->FishingLineComponent->SetVisibility(false);

	for (uint32 i = 0; i < DotMotionBuffer.Capacity(); i++)
	{
		DotMotionBuffer[i] = BufferIgnoreValue;
	}

	// Stop Checking Motion Value
	if (MotionTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(MotionTimer);
		MotionTimer.Invalidate();
	}

	Super::Deactivate();
}

void UFishingComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	OwningPlayer->FishingLineComponent->SetVisibility(true);
	OwningPlayer->FishingRodMeshComponent->SetVisibility(true);

	StartCheckingMotionValue();
}

void UFishingComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

