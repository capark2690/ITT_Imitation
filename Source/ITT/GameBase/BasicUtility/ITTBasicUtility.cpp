// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTBasicUtility.h"

#include "ITTGameConfig.h"
#include "Engine/World.h"

#include "GameBase/GameInstance/ITTGameInstanceBase.h"
#include "Player/PlayerController/ITTPlayerController_InGame.h"
#include "Character/Player/ITTCharacter_Player.h"
#include "Engine/Level.h"
#include "Level/ITTLevelScriptActor.h"


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

AITTLevelScriptActor* UITTBasicUtility::GetITTLevelScriptActor()
{
	if (UWorld* World = UITTBasicUtility::GetITTWorld())
	{
		if (ULevel* Level = World->GetLevel(0))
		{
			ALevelScriptActor* LevelScriptActor = Level->GetLevelScriptActor();
			return Cast<AITTLevelScriptActor>(LevelScriptActor);
		}
	}

	return nullptr;
}

AITTPlayerControllerBase* UITTBasicUtility::GetFirstPlayerController()
{
	if (UITTBasicUtility::GetITTWorld())
	{
		return Cast<AITTPlayerControllerBase>(UITTBasicUtility::GetITTWorld()->GetFirstPlayerController());
	}

	return nullptr;
}

AITTPlayerController_InGame* UITTBasicUtility::GetPlayerController(EITTPlayerCharacterType PlayerCharacterType)
{
	if (UWorld* World = UITTBasicUtility::GetITTWorld())
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			if (AITTPlayerController_InGame* Player_InGame = Cast<AITTPlayerController_InGame>(Iterator->Get()))
			{
				if (Player_InGame->GetPlayerCharacterType() == PlayerCharacterType)
				{
					return Player_InGame;
				}
			}
		}
	}
	
	return nullptr;
}

AITTCharacter_Player* UITTBasicUtility::GetPlayerCharacter(EITTPlayerCharacterType PlayerCharacterType)
{
	if (AITTPlayerController_InGame* PlayerController = UITTBasicUtility::GetPlayerController(PlayerCharacterType))
	{
		if (PlayerController->GetPlayerCharacterType() == PlayerCharacterType)
		{
			if (AITTCharacter_Player* Character = Cast<AITTCharacter_Player>(PlayerController->GetPawn()))
			{
				return Character;
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