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

	//ī�޶�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UCameraComponent* CameraComponent;
	
	// ī�޶� �޽�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UStaticMeshComponent* HMDMesh;
	
	// ���� ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* LeftHand;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	USkeletalMeshComponent* LeftHandMesh;
	
	// ������ ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UMotionControllerComponent* RightHand;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	USkeletalMeshComponent* RightHandMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|FishingComponent")
	class UFishingComponent* FishingComponent;
	
	// ���ô� �޽� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	UStaticMeshComponent* FishingRodMeshComponent;

};
