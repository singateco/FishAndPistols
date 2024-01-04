// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldDropWidgetActor.h"

#include "GoldDropUI.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"

// Sets default values
AGoldDropWidgetActor::AGoldDropWidgetActor()
	:
	RootComp(CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"))),
	WidgetComponent(CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp")))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(RootComp);
	WidgetComponent->SetupAttachment(RootComp);
}

void AGoldDropWidgetActor::SetGoldText(const int32 GoldAmount)
{
	Cast<UGoldDropUI>(WidgetComponent->GetUserWidgetObject())->GoldText->SetText(FText::AsNumber(GoldAmount));
}

// Called when the game starts or when spawned
void AGoldDropWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(3.f);
	SetGoldText(Amount);
}

// Called every frame
void AGoldDropWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + FVector(0, 0, FMath::Abs(FMath::Sin(GetGameTimeSinceCreation()) * 5.f)));
}

