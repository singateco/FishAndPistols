// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FISHANDPISTOLS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	// ============= FUNCTIONS ==============

	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ============= PROPERTIES =============

	// 카메라
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UCameraComponent* CameraComponent;

	// 카메라 메시
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UStaticMeshComponent* HMDMesh;

	// 왼쪽 손
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* LeftHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	USkeletalMeshComponent* LeftHandMesh;

	// 오른쪽 손
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UMotionControllerComponent* RightHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	USkeletalMeshComponent* RightHandMesh;

};
