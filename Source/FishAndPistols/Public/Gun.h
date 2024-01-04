// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"


UCLASS()
class FISHANDPISTOLS_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//----------------------------Variable--------------------------------
public:

	UPROPERTY()
	class USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* GunMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* BulletREF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* EffectREF;

	UPROPERTY(EditAnywhere, Category = Effect)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = Effect)
	class USoundBase* DryFireSound;

	UPROPERTY(EditAnywhere, Category = Effect)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = Effect)
	class UStaticMeshComponent* Laser;

	UPROPERTY(EditAnywhere, Category = Effect)
	class UMaterialInterface* BulletDecal;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* BulletWidget;

	UPROPERTY(EditAnywhere)
	class UBulletAmount* BulletWidgetObject;

	UPROPERTY(EditAnywhere)
	float GunRange = 10000;

	UPROPERTY(EditAnywhere)
	int Bullet;

	UPROPERTY(EditAnywhere)
	int MaxBullet;

	UPROPERTY(EditAnywhere, Category = Upgrade)
	bool IsExtendedMag = false;

	UPROPERTY(EditAnywhere, Category = Upgrade)
	bool IsRazor = false;


	//----------------------------Function--------------------------------
	virtual void ActionFire();
	void GunFireEffect();

	UFUNCTION()
	void UpgradeExtendedMag(class UUpgradeComponent* UpgradeComponent);

	UFUNCTION()
	void UpgradeLaserSight(UUpgradeComponent* UpgradeComponent);

};
