// Fill out your copyright notice in the Description page of Project Settings.


#include "HandAnimInstance.h"

void UHandAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//CurrentPoseAlpha 변수의 값을 PoseAlpha 변수의 값이 되도록 서서히 변경한다.
	CurrentPoseAlphaPoint_cpp = FMath::Lerp(CurrentPoseAlphaPoint_cpp, PoseAlphaPoint_cpp, DeltaSeconds * 13.0f);
	CurrentPoseAlphaThumbUp_cpp = FMath::Lerp(CurrentPoseAlphaThumbUp_cpp, PoseAlphaThumbUp_cpp, DeltaSeconds * 13.0f);

}
