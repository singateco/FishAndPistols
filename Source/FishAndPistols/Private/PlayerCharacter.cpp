// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "FishingComponent.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
	:
	CameraComponent(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"))),
	HMDMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"))),
	LeftHand(CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Hand Motion Controller"))),
	LeftHandMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"))),
	RightHand(CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Hand"))),
	RightHandMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"))),
	FishingComponent(CreateDefaultSubobject<UFishingComponent>(FName("Fishing Component")))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up attachments.
	CameraComponent->SetupAttachment(RootComponent);
	HMDMesh->SetupAttachment(CameraComponent);

	LeftHand->SetupAttachment(RootComponent);
	LeftHandMesh->SetupAttachment(LeftHand);

	RightHand->SetupAttachment(RootComponent);
	RightHandMesh->SetupAttachment(RightHand);

	// Set up tracking motion sources.
	LeftHand->SetTrackingMotionSource(FName("Left"));
	RightHand->SetTrackingMotionSource(FName("Right"));

	FishingComponent->Activate();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	// 헤드 마운트 디스플레이 장비의 기준 위치를 스테이지로 설정한다.
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	FishingComponent->SetupPlayerInputComponent(PlayerInputComponent);
}
