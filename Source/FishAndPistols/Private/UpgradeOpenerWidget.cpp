// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeOpenerWidget.h"

#include "Components/Image.h"

void UUpgradeOpenerWidget::SetPercent(const float InPercent)
{
	Percent = FMath::Clamp(InPercent, 0.f, 1.f);

	if (nullptr == MaterialInstance)
	{
		check(MaterialInterface)
		MaterialInstance = UMaterialInstanceDynamic::Create(MaterialInterface, this);
	}

	check(MaterialInstance)
	MaterialInstance->SetScalarParameterValue(FName("Percent"), Percent);
}

void UUpgradeOpenerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (nullptr == MaterialInstance)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(MaterialInterface, this);
	}

	ImageBox->SetBrushFromMaterial(MaterialInstance);
	SetPercent(Percent);
}

