// Fill out your copyright notice in the Description page of Project Settings.


#include "FishCable.h"

#include "CableComponent.h"

AFishCable::AFishCable()
{
	this->CableComponent->bAttachStart = true;
	this->CableComponent->bAttachEnd = true;
	this->CableComponent->EndLocation = FVector(0, 0, 0);
}
