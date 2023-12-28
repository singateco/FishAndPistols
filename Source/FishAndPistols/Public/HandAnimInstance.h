// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HandAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FISHANDPISTOLS_API UHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnimSetting)
	bool bMirror_cpp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimSetting)
	float PoseAlphaGrasp_cpp = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimSetting)
	float PoseAlphaIndexCurl_cpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimSetting)
	float PoseAlphaPoint_cpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimSetting)
	float PoseAlphaThumbUp_cpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimSetting)
	float CurrentPoseAlphaThumbUp_cpp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimSetting)
	float CurrentPoseAlphaPoint_cpp = 0;
};
