// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "FishSpawner.generated.h"

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
	void SpawnFish();

	UFUNCTION()
	void SlowdownTime();

	UFUNCTION(BlueprintCallable)
	void SpawnMultipleFish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmountToSpawn {6};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFish> FishClass;

	UPROPERTY()
	UTimelineComponent* TimeLineComp;

	UPROPERTY()
	UCurveFloat* TimeLineCurve;

	FOnTimelineFloat InterpFunction{};

	UFUNCTION()
	void TimelineUpdate(float Val);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
