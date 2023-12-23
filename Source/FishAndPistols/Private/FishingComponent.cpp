// Fill out your copyright notice in the Description page of Project Settings.


#include "FishingComponent.h"
#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Components/ArrowComponent.h"
#include "Misc/DateTime.h"


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
		DotMotionBuffer[i] = -9999;
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


	// Start checking for motion value for detecting fishing motion
	GetWorld()->GetTimerManager().SetTimer(MotionTimer, this, &UFishingComponent::CheckMotionValue, 0.05f, true);
}


// Called every frame
void UFishingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	FVector RightHandLocation = OwningPlayer->RightHandMesh->GetComponentLocation();
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
	FVector PlayerForward = OwningPlayer->GetArrowComponent()->GetForwardVector();
	FVector RightHandLocation = OwningPlayer->RightHandMesh->GetComponentLocation();

	DotMotionBuffer[BufferIndex] = PlayerForward.Dot(RightHandLocation);
	BufferIndex = DotMotionBuffer.GetNextIndex(BufferIndex);

	double min = DotMotionBuffer[0];
	double max = DotMotionBuffer[0];

	for (uint32 i = 0; i < DotMotionBuffer.Capacity(); i++)
	{
		if (DotMotionBuffer[i] == -9999)
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

	if (min - max < -52.5)
	{
		FDateTime Now = FDateTime::Now();
		UE_LOG(LogTemp, Warning, TEXT("Detected, %d, %d"), Now.GetSecond(), Now.GetMillisecond());
	}
	//UE_LOG(LogTemp, Warning, TEXT("Min Max Difference = %.2f"), min - max);
}

void UFishingComponent::RightIndexTrigger(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Triggered"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger Completed"))
	}
}

void UFishingComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

