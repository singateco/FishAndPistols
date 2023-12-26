// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FishSpawner.generated.h"

UCLASS()
class FISHANDPISTOLS_API AFishSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFishSpawner();

	UFUNCTION(BlueprintCallable)
	void SpawnFish();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFish> FishClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
