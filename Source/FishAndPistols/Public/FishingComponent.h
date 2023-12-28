// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "Containers/CircularBuffer.h"
#include "FishingComponent.generated.h"

UENUM(BlueprintType)
enum class EFishingStatus: uint8
{
	Idle,
	Fishing
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFishCaught);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FISHANDPISTOLS_API UFishingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFishingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializeComponent() override;

	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* InputComponent);

	UFUNCTION()
	void CheckMotionValue();

	UFUNCTION()
	void MotionDetected(bool bBackward);

	UFUNCTION(BlueprintCallable)
	void MakeFishHook();

	UPROPERTY()
	class APlayerCharacter* OwningPlayer;

	// Value to determine the impulse power to throw fish line (hook)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HookThrowSpeed{ 500 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* RightIndexTriggerInputAction;

	// Motion Buffer
	TCircularBuffer<double> DotMotionBuffer {8};

	// Sentinel value for the motion buffer.
	const float BufferIgnoreValue {-9999};

	// Index Value for the buffer.
	uint32 BufferIndex {0};

	// Threshold for the buffer.
	UPROPERTY(EditAnywhere)
	float MotionThreshold {-45.f};

	UPROPERTY()
	FTimerHandle MotionTimer;

	UPROPERTY(BlueprintAssignable)
	FFishCaught OnFishCaught;

	UPROPERTY(VisibleAnywhere)
	EFishingStatus Status {EFishingStatus::Idle};

	UPROPERTY(VisibleAnywhere)
	bool bIsAbleToDetectMotion {false};

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float MotionTimerCooldownSeconds {3.f};

	UPROPERTY()
	FTimerHandle MotionDetectedTimer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFishHook> HookClass;

	UPROPERTY(EditAnywhere)
	AFishHook* Hook;



private:
	void RightIndexTrigger(const FInputActionValue& Value);
	void FishingStarted();
	void CaughtFish();

public:
	virtual void Deactivate() override;
};
