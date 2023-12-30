// Fill out your copyright notice in the Description page of Project Settings.


#include "HandAnimComponent.h"
#include "EnhancedInputComponent.h"
#include "HandAnimInstance.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UHandAnimComponent::UHandAnimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHandAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = GetOwner<APlayerCharacter>();

	if(nullptr != Player)
	{
		HandAnim_Left = Cast<UHandAnimInstance>(Player->LeftHandMesh->GetAnimInstance());
		//왼손은 mirror 변수를 바꿈
		if(HandAnim_Left)
		{
			HandAnim_Left->bMirror_cpp = true;
		}

		HandAnim_Right = Cast<UHandAnimInstance>(Player->RightHandMesh->GetAnimInstance());
		
		if (HandAnim_Right)
		{
			HandAnim_Right->bMirror_cpp = false;
		}
	}
}


// Called every frame
void UHandAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHandAnimComponent::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent,
	TArray<UInputAction*> InputActions)
{

	//왼쪽 검지 트리거 터치
	EnhancedInputComponent->BindAction(InputActions[0], ETriggerEvent::Triggered, this, &UHandAnimComponent::Left_Trigger_Touch);
	EnhancedInputComponent->BindAction(InputActions[0], ETriggerEvent::Completed, this, &UHandAnimComponent::Left_Trigger_Touch);

	//왼쪽 검지 트리거 누르는 값
	EnhancedInputComponent->BindAction(InputActions[1], ETriggerEvent::Triggered, this, &UHandAnimComponent::Left_Trigger_Value);
	EnhancedInputComponent->BindAction(InputActions[1], ETriggerEvent::Completed, this, &UHandAnimComponent::Left_Trigger_Value);

	//오른쪽 검지 트리거 터치
	EnhancedInputComponent->BindAction(InputActions[2], ETriggerEvent::Triggered, this, &UHandAnimComponent::Right_Trigger_Touch);
	EnhancedInputComponent->BindAction(InputActions[2], ETriggerEvent::Completed, this, &UHandAnimComponent::Right_Trigger_Touch);

	//오른쪽 검지 트리거 누르는 값
	EnhancedInputComponent->BindAction(InputActions[3], ETriggerEvent::Triggered, this, &UHandAnimComponent::Right_Trigger_Value);
	EnhancedInputComponent->BindAction(InputActions[3], ETriggerEvent::Completed, this, &UHandAnimComponent::Right_Trigger_Value);
	
}


void UHandAnimComponent::Left_Trigger_Touch(const FInputActionValue& value)
{
	if(nullptr != HandAnim_Left)
	{
		HandAnim_Left->PoseAlphaPoint_cpp = value.Get<bool>() == true ? 0 : 1.0f;
	}
}

void UHandAnimComponent::Left_Trigger_Value(const FInputActionValue& value)
{
	if(nullptr != HandAnim_Left)
	{
		HandAnim_Left->PoseAlphaIndexCurl_cpp = value.Get<float>();
		
	}
}

void UHandAnimComponent::Right_Trigger_Touch(const FInputActionValue& value)
{
	if (nullptr != HandAnim_Right)
	{
		HandAnim_Right->PoseAlphaPoint_cpp = value.Get<bool>() == true ? 0 : 1.0f;
	}
}

void UHandAnimComponent::Right_Trigger_Value(const FInputActionValue& value)
{
	if (nullptr != HandAnim_Right)
	{
		HandAnim_Right->PoseAlphaIndexCurl_cpp = value.Get<float>();
	}
}

