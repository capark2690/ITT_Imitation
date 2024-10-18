// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTDefine_GameBase.generated.h"


// ==================== Enum ==================== //
// ========== GameInstance ========== //
UENUM()
enum class EITTLaunchProcess : uint8
{
	None = 0,
 
	CreateBasicUtility,
	CreateGameManager,
	RegisterTick,
	ProcessFinished,

	End
};
// ================================== //


// ========== Scene ========== //
UENUM()
enum class EITTSceneType : uint32
{
	// MainScene * 7 / SubScene * 8 / Detail1 * 8 / Detail2 * 8
	
	None = 0b0,

	ProductionLogo = 0b01,
	GameLogo = 0b10,
	
	Title = 0b11,
	LocalPlay_SelectInput = 0b100,
	LocalPlay_SelectCharacter = 0b101,

	Ch1_Start = 0b01 << 24 | 0b01 << 16,
	Ch2_Nail = 0b10 << 24 | 0b01 << 16,
	Ch2_Machine = 0b10 << 24 | 0b10 << 16,
};

UENUM()
enum class EITTLoadingType : uint8
{
	None = 0,
};
// =========================== //
// ============================================== //


// ==================== Delegate ==================== //
// ========== Level ========== //
DECLARE_DELEGATE_OneParam(FITTOnLoadLevelComplete, const FString&);
// =========================== //
// ================================================== //