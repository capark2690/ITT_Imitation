// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameBase/GameManager/ITTSingleton.h"
#include "ITTCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTCameraManager : public UObject, public TITTSingleton<UITTCameraManager>
{
	GENERATED_BODY()


public:
	UITTCameraManager();

	
	// ========== Split screen ========== //
	void SetForceDisableSplitscreen(bool bDisable);
	// ================================== //

	
#define CameraMgr UITTCameraManager::GetInstance()
};
