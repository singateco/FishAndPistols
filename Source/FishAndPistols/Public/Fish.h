// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fish.generated.h"

UCLASS()
class FISHANDPISTOLS_API AFish : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFish();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGoldDropWidgetActor> GoldDropWidgetActorClass;

	UPROPERTY(EditAnywhere)
	float ZUpwardLimit {2800};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHP {1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GoldDropAmount {1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UpwardImpulseForce{ 200000 };

	UPROPERTY(EditAnywhere)
	float DefaultSpeed {1500};

	//물고기 터질때 이펙트와 사운드 by Undoe
	UPROPERTY(EditAnywhere)
	class USoundBase* CoinSound;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ExplosionEffect;

	void Die();
	void FishDeadEffect();

	UFUNCTION()
	void TakeDamage(int32 Damage);
};
