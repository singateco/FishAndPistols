// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "CableComponent.h"
#include "EnhancedInputComponent.h"
#include "ShootingComponent.h"
#include "FishingComponent.h"
#include "HandAnimComponent.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineMeshComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
	:
 	CameraComponent(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"))),
 	HMDMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"))),
 	LeftHand(CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Hand Motion Controller"))),
 	LeftHandMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"))),
 	RightHand(CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Hand Motion Controller"))),
 	RightHandMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"))),
 	FishingComponent(CreateDefaultSubobject<UFishingComponent>(TEXT("Fishing Component"))),
//슈팅컴포넌트
	ShootingComponent(CreateDefaultSubobject<UShootingComponent>(TEXT("Shooting Component"))),
	HandAnimComponent(CreateDefaultSubobject<UHandAnimComponent>(TEXT("Hand Anim Component"))),
 	FishingRodMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fishing Rod Mesh Comp"))),
	FishingLineComponent(CreateDefaultSubobject<USplineMeshComponent>(TEXT("Fishing Line Component"))),
	FishCable(CreateDefaultSubobject<UCableComponent>(TEXT("Fishing Rod Cable")))
 {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up attachments.
	CameraComponent->SetupAttachment(RootComponent);
	HMDMesh->SetupAttachment(CameraComponent);

	LeftHand->SetupAttachment(RootComponent);
	LeftHandMesh->SetupAttachment(LeftHand);
	LeftHandMesh->SetRelativeRotation(FRotator(90, -180, -25));
	LeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightHand->SetupAttachment(RootComponent);
	RightHandMesh->SetupAttachment(RightHand);
	RightHandMesh->SetRelativeRotation(FRotator(90, 0, 25));
	RightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	FishingRodMeshComponent->SetupAttachment(RightHandMesh, FName("palm_rSocket"));
	FishingRodMeshComponent->SetMobility(EComponentMobility::Movable);
	FishingLineComponent->SetupAttachment(FishingRodMeshComponent, FName("LineStart"));
	FishingLineComponent->SetMobility(EComponentMobility::Movable);
	FishingLineComponent->SetStartPosition(FVector::ZeroVector);

	// 낚시줄 세팅
	FishCable->SetupAttachment(FishingRodMeshComponent, TEXT("LineEnd"));
	FishCable->bAttachStart = true;
	FishCable->bAttachEnd = true;
	FishCable->EndLocation = FVector(0, 0, 0);
	FishCable->SetVisibility(false);

	// (X=6.070411,Y=0.112364,Z=4.035356)
	// (Pitch=2.401839,Yaw=629.462922,Roll=-478.018271)
	// 0.25

	// Set up tracking motion sources.
	LeftHand->SetTrackingMotionSource(FName("Left"));
	RightHand->SetTrackingMotionSource(FName("Right"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ShootingComponent->Deactivate();
	FishingComponent->Activate(false);

	// 헤드 마운트 디스플레이 장비의 기준 위치를 스테이지로 설정한다.
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FishingRodMeshComponent->IsVisible())
	{
		FishingLineComponent->SetEndPosition(FishingRodMeshComponent->GetSocketTransform(FName("LineEnd"), RTS_Component).GetLocation());
	}

	FVector EndLoc = FishingRodMeshComponent->GetSocketLocation(FName("LineEnd"));
	//DrawDebugPoint(GetWorld(), EndLoc, 25.f, FColor::Cyan);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	FishingComponent->SetupPlayerInputComponent(PlayerInputComponent);
	ShootingComponent->SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		HandAnimComponent->SetupPlayerInputComponent(EnhancedInputComponent, InputActions);
	}

}
