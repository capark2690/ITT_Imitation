// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTGameProcessManager.h"


// ========== Character ========== //
void UITTGameProcessManager::ResetControllerIdToCharacter()
{
	ControllerIdToCharacterType.Reset();
}

void UITTGameProcessManager::AddControllerIdToCharacterType(uint8 ContollerId, EITTPlayerCharacterType Character)
{
	ControllerIdToCharacterType.Emplace(ContollerId, Character);
}

EITTPlayerCharacterType UITTGameProcessManager::GetControllerCharacterType(uint8 ContollerId)
{
	if (ControllerIdToCharacterType.Contains(ContollerId))
	{
		return *ControllerIdToCharacterType.Find(ContollerId);
	}

	return EITTPlayerCharacterType::None;
}
// =============================== //