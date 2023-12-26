// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpadeAce.generated.h"

UCLASS()
class FISHANDPISTOLS_API ASpadeAce : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpadeAce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//----------------------------Variable--------------------------------
private:

	UPROPERTY()
		class UStaticMeshComponent* SpadeAce;

	UPROPERTY()
		class UStaticMeshComponent* BulletREF;

	float GunRange = 2000;

	//----------------------------Function--------------------------------

};
