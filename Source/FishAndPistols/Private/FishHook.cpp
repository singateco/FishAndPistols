// Fill out your copyright notice in the Description page of Project Settings.


#include "FishHook.h"

#include "Components/BoxComponent.h"

// Sets default values
AFishHook::AFishHook()
	:
	BoxComp(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"))),
	MeshComp(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(BoxComp);
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void AFishHook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFishHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

