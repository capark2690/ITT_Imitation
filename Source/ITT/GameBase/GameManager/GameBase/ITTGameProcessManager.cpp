// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTGameProcessManager.h"


// ========== Character ========== //
void UITTGameProcessManager::ResetControllerIdToCharacter()
{
	ControllerIdToCharacter.Reset();
}

void UITTGameProcessManager::AddControllerIdToCharacter(uint8 ContollerId, EITTCharacter_Player Character)
{
	ControllerIdToCharacter.Emplace(ContollerId, Character);
}

EITTCharacter_Player UITTGameProcessManager::GetControllerCharacter(uint8 ContollerId)
{
	if (ControllerIdToCharacter.Contains(ContollerId))
	{
		return *ControllerIdToCharacter.Find(ContollerId);
	}

	return EITTCharacter_Player::None;
}
// =============================== //