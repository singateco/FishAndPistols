// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FishSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveOver);

UCLASS()
class FISHANDPISTOLS_API AFishSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFishSpawner();


	UFUNCTION()
	void BindWithPlayer(class APlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	void SpawnFish(TSubclassOf<class AFish> InClass);

	UFUNCTION()
	void SlowdownTime();

	UFUNCTION(BlueprintCallable)
	void SpawnMultipleFish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmountToSpawn {6};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFish> FishClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFish> RareFishClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFish> ChestFishClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFish> SharkClass;

	UPROPERTY(VisibleAnywhere)
	bool bCanSpawnRareFish {false};

	UPROPERTY(VisibleAnywhere)
	bool bCanSpawnChestFish {false};

	UPROPERTY(VisibleAnywhere)
	bool bCanSpawnSharkFish {false};

	// 슬로우 모션 속도
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.0f, UIMin = 0.0f, ClampMax = 1.0f, UIMax = 1.0f))
	float SlowMotionTimeScale {0.4f};

	UPROPERTY(EditAnywhere)
	float SlowDownStartSecond {1.5f};

	UPROPERTY(EditAnywhere)
	float SlowDownEndSecond {3.1f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaveOverSecond {10.f};

	UPROPERTY()
	FTimerHandle WaveTimerHandle;

	UPROPERTY(BlueprintAssignable)
	FWaveOver OnWaveOverDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
