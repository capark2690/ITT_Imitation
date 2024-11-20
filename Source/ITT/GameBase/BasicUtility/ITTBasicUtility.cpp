// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTBasicUtility.h"

#include "ITTGameConfig.h"
#include "Engine/World.h"

#include "GameBase/GameInstance/ITTGameInstanceBase.h"
#include "Player/PlayerController/ITTPlayerController_InGame.h"
#include "Character/Player/ITTCharacter_Player.h"


TObjectPtr<UITTBasicUtility> UITTBasicUtility::Instance = nullptr;


UITTBasicUtility::UITTBasicUtility()
{
}


// ========== Instance ========== //
TObjectPtr<UITTBasicUtility> UITTBasicUtility::CreateInstance()
{
	Instance = ITTNewObject<UITTBasicUtility>();
	if (Instance)
	{
		Instance->AddToRoot();
	}
	
	return Instance;
}

void UITTBasicUtility::DestroyInstance()
{
	if (IsValid(Instance))
	{
		Instance->RemoveFromRoot();
		ITTDeleteObject(Instance);
	}
}

bool UITTBasicUtility::Initialize(UITTGameInstanceBase* _ITTGameInstance)
{
	ITTGameInstance = _ITTGameInstance;
	
	Instance->CreateCompositionObjects();
	
	return true;
}

void UITTBasicUtility::Finalize()
{
	Instance->DestroyCompositionObjects();

	ITTGameInstance = nullptr;
}
// ============================== //


// ========== Composition ========== //
void UITTBasicUtility::CreateCompositionObjects()
{
	ITTGameConfig = ITTNewObject<UITTGameConfig>();
	if (ITTGameConfig)
	{
		ITTGameConfig->AddToRoot();
	}
}

void UITTBasicUtility::DestroyCompositionObjects()
{
	if (IsValid(ITTGameConfig))
	{
		ITTGameConfig->RemoveFromRoot();
		ITTDeleteObject(ITTGameConfig);
	}
}
// ================================= //


// ==================== Getter ==================== //
// ========== BasicUtility ========== //
TWeakObjectPtr<UITTGameInstanceBase> UITTBasicUtility::GetITTGameInstance()
{
	if (IsValid(Instance))
	{
		return Instance->ITTGameInstance;
	}

	return nullptr;
}

UWorld* UITTBasicUtility::GetITTWorld()
{
	TWeakObjectPtr<UITTGameInstanceBase> GameInstance = GetITTGameInstance();
	if (GameInstance != nullptr)
	{
		return GameInstance->GetWorld();
	}

	return nullptr;
}

AITTPlayerController_InGame* UITTBasicUtility::GetPlayerController(EITTCharacter_Player PlayerCharacter)
{
	if (UWorld* World = UITTBasicUtility::GetITTWorld())
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			if (AITTPlayerController_InGame* Player_InGame = Cast<AITTPlayerController_InGame>(Iterator->Get()))
			{
				if (Player_InGame->GetPlayerCharacter() == PlayerCharacter)
				{
					return Player_InGame;
				}
			}
		}
	}
	
	return nullptr;
}

AITTCharacter_Player* UITTBasicUtility::GetPlayerCharacter(EITTCharacter_Player PlayerCharacter)
{
	if (UWorld* World = UITTBasicUtility::GetITTWorld())
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			if (AITTPlayerController_InGame* Player_InGame = Cast<AITTPlayerController_InGame>(Iterator->Get()))
			{
				if (Player_InGame->GetPlayerCharacter() == PlayerCharacter)
				{
					if (AITTCharacter_Player* Character = Cast<AITTCharacter_Player>(Player_InGame->GetPawn()))
					{
						return Character;
					}
				}
			}
		}
	}
	
	return nullptr;
}
// ================================== //


// ========== GameConfig ========== //
// -- Table -- //
const FString& UITTBasicUtility::GetTableListPath()
{
	ITTCHECK(Instance);
	ITTCHECK(Instance->ITTGameConfig);
	
	return Instance->ITTGameConfig->GetTableListPath();
}
// ================================ //
// ================================================ //