// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSceneBase.h"

#include "Engine/Level.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

#include "ITTUtilityFunctionLibrary.h"
#include "GameBase/BasicUtility/ITTBasicUtility.h"
#include "Level/ITTLevelScriptActor.h"

#include "GameBase/GameManager/Data/ITTTableManager.h"
#include "Data/Table/Tables/GameBase/ITTTable_Scene.h"

#include "GameBase/GameManager/Camera/ITTCameraManager.h"
#include "Data/DataAssets/Camera/SceneCamera/ITTData_SceneCamera.h"


UITTSceneBase::UITTSceneBase()
	: SceneType(EITTSceneType::None)
{
}


void UITTSceneBase::Initialize(EITTSceneType _SceneType)
{
	SceneType = _SceneType;

	FString SceneTypeName = UITTUtilityFunctionLibrary::ConvertEnumToString(FString("EITTSceneType"), SceneType);
	ITTLOG(Log, TEXT("[%s] Initialize scene [SceneType : %s]"), *ITTSTRING_FUNC, *SceneTypeName);
	
	SetSceneCamera();
}

void UITTSceneBase::Finalize()
{
	FString SceneTypeName = UITTUtilityFunctionLibrary::ConvertEnumToString(FString("EITTSceneType"), SceneType);
	ITTLOG(Log, TEXT("[%s] Finalize scene [SceneType : %s]"), *ITTSTRING_FUNC, *SceneTypeName);
}

void UITTSceneBase::Tick(float DeltaTime)
{
}


// ========== Finish ========== //
void UITTSceneBase::PrepareToFinish(EITTSceneType NextSceneType, EITTLoadingType LoadingType)
{
	bool bDelegateBound = OnReadyToFinishDelegate.ExecuteIfBound();	// Call ITTSceneManager::ChangeSceneState()
	if (!bDelegateBound)
	{
		FString CurrentSceneTypeName = UITTUtilityFunctionLibrary::ConvertEnumToString(TEXT("EITTSceneType"), SceneType);
		FString NextSceneTypeName = UITTUtilityFunctionLibrary::ConvertEnumToString(TEXT("EITTSceneType"), NextSceneType);
		ITTLOG(Error, TEXT("[%s] OnReadyToFinishDelegate isn't bound [CurrentSceneType : %s] [NextSceneType : %s]")
			, *ITTSTRING_FUNC, *CurrentSceneTypeName, *NextSceneTypeName);
	}
}

void UITTSceneBase::PrepareToFinish_Immediately(EITTSceneType NextSceneType, EITTLoadingType LoadingType)
{
	bool bDelegateBound = OnReadyToFinishDelegate.ExecuteIfBound();	// Call ITTSceneManager::ChangeSceneState()
	if (!bDelegateBound)
	{
		FString CurrentSceneTypeName = UITTUtilityFunctionLibrary::ConvertEnumToString(TEXT("EITTSceneType"), SceneType);
		FString NextSceneTypeName = UITTUtilityFunctionLibrary::ConvertEnumToString(TEXT("EITTSceneType"), NextSceneType);
		ITTLOG(Error, TEXT("[%s] OnReadyToFinishDelegate isn't bound [CurrentSceneType : %s] [NextSceneType : %s]")
			, *ITTSTRING_FUNC, *CurrentSceneTypeName, *NextSceneTypeName);
	}
}
// ============================ //


// ========== Camera ========== //
void UITTSceneBase::SetSceneCamera()
{
	UWorld* World = UITTBasicUtility::GetITTWorld();
	if (!World)
	{
		return;
	}
	
	if (!TableMgr || !CameraMgr)
	{
		return;
	}
	
	if (UITTTable_Scene* SceneTable = TableMgr->GetITTTable<UITTTable_Scene>(UITTTable_Scene::GetTableName()))
	{
		UITTData_SceneCamera* SceneCameraData = SceneTable->GetSceneCameraData(SceneType);

		if (SceneCameraData)
		{
			CameraMgr->SetForceDisableSplitscreen(SceneCameraData->bForceDisableSplitscreen);

			AITTLevelScriptActor* LevelScriptActor = Cast<AITTLevelScriptActor>(World->GetLevel(0)->GetLevelScriptActor());
			if (LevelScriptActor)
			{
				if (APlayerController* Player1 = UGameplayStatics::GetPlayerControllerFromID(World, 0))
				{
					if (SceneCameraData->bViewTargetPlayer1IsPawn)
					{
						Player1->SetViewTarget(Player1->GetPawn());
					}
					else
					{
						if (AActor* ViewTarget_Player1 = LevelScriptActor->GetViewTargetActor(SceneCameraData->ViewTargetName_Player1))
						{
							Player1->SetViewTarget(ViewTarget_Player1);
						}
					}
				}

				if (APlayerController* Player2 = UGameplayStatics::GetPlayerControllerFromID(World, 1))
				{
					if (SceneCameraData->bViewTargetPlayer2IsPawn)
					{
						Player2->SetViewTarget(Player2->GetPawn());
					}
					else
					{
						if (AActor* ViewTarget_Player2 = LevelScriptActor->GetViewTargetActor(SceneCameraData->ViewTargetName_Player2))
						{
							Player2->SetViewTarget(ViewTarget_Player2);
						}
					}
				}
			}
		}
	}
}
// ============================ //