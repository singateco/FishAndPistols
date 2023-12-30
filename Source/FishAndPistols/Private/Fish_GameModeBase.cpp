// Fill out your copyright notice in the Description page of Project Settings.


#include "Fish_GameModeBase.h"

void AFish_GameModeBase::AddGold(int32 Amount)
{
	Gold += Amount;

	OnGoldAmountChanged.Broadcast(Gold);
}

bool AFish_GameModeBase::SpendGold(int32 Amount)
{
	if (Amount > Gold)
	{
		return false;
	}

	Gold -= Amount;
	OnGoldAmountChanged.Broadcast(Gold);
	return true;	
}


