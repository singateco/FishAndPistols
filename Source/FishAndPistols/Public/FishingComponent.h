// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "Containers/CircularBuffer.h"
#include "FishingComponent.generated.h"


class APlayerCharacter;

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

	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* InputComponent);

	UFUNCTION()
	void CheckMotionValue();

	UPROPERTY()
	class APlayerCharacter* OwningPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* RightIndexTriggerInputAction;

	TCircularBuffer<double> DotMotionBuffer {16};

	uint32 BufferIndex {0};

	UPROPERTY()
	FTimerHandle MotionTimer;

private:
	void RightIndexTrigger(const FInputActionValue& Value);

public:
	virtual void InitializeComponent() override;
};
