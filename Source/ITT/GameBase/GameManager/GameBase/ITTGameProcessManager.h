// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameBase/GameManager/ITTSingleton.h"
#include "Character/ITTDefine_Character.h"
#include "ITTGameProcessManager.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTGameProcessManager : public UObject, public TITTSingleton<UITTGameProcessManager>
{
	GENERATED_BODY()

public:
	// ========== Character ========== //
	void ResetControllerIdToCharacter();
	
	void AddControllerIdToCharacterType(uint8 ContollerId, EITTPlayerCharacterType CharacterType);

	EITTPlayerCharacterType GetControllerCharacterType(uint8 ContollerId);
	// =============================== //

	
private:
	// ========== Character ========== //
	TMap<uint8, EITTPlayerCharacterType> ControllerIdToCharacterType;
	// =============================== //

	
#define GameProcessMgr UITTGameProcessManager::GetInstance()
};
