// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldDropWidgetActor.generated.h"

UCLASS()
class FISHANDPISTOLS_API AGoldDropWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoldDropWidgetActor();

	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY()
	int32 Amount;

	UFUNCTION()
	void SetGoldText(int32 GoldAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
