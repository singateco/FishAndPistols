// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletAmount.h"

#include "Components/TextBlock.h"


void UBulletAmount::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}

void UBulletAmount::UpdateBulletAmount(int Bullet)
{

	FString txt = FString::Printf(TEXT("%d"), Bullet);
	BulletText->SetText(FText::FromString(txt));
}
