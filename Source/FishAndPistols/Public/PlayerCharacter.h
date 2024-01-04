// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
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

	void HoldUpgradeWidget(const FInputActionInstance& InputActionInstance);
	void ToggleUpgradeWidget(const FInputActionInstance& InputActionInstance);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// ============= PROPERTIES =============

	//카메라
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UWidgetInteractionComponent* WidgetInteractionComponent;

	// 왼손 위 골드 표시 위젯
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Widgets")
	class UWidgetComponent* StatusWidgetComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Widgets")
	UUserWidget* StatusWidget;

	// 왼손 위 업그레이드 창 열기
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Widgets")
	UWidgetComponent* OpenerWidgetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MySettings|Widgets")
	class UUpgradeOpenerWidget* OpenerWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|FishingComponent")
	class UFishingComponent* FishingComponent;

	//슈팅 컴포넌트
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|ShootingComponent")
	class UShootingComponent* ShootingComponent;

	//손 애니메이션 컴포넌트
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|HandAnimComponent")
	class UHandAnimComponent* HandAnimComponent;

	// 낚시대 메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	UStaticMeshComponent* FishingRodMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class USplineMeshComponent* FishingLineComponent;

	// 업그레이드 컴포넌트
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|UpgradeComponent")
	class UUpgradeComponent* UpgradeComponent;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UCableComponent* FishCable;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings|Input")
	class UInputMappingContext* InteractMappingContext;

	UPROPERTY(EditAnywhere, Category = "MySettings|Input")
	TArray<class UInputAction*> InputActions;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings|Input")
	UInputAction* InputAction_HoldY;


	
};
