// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSceneBase.h"

#include "ITTUtilityFunctionLibrary.h"
#include "Data/DataAssets/Camera/SceneCamera/ITTData_SceneCamera.h"

#include "GameBase/GameManager/Data/ITTTableManager.h"
#include "Data/Table/Tables/GameBase/ITTTable_Scene.h"

#include "GameBase/GameManager/Camera/ITTCameraManager.h"


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
	if (TableMgr && CameraMgr)
	{
		if (UITTTable_Scene* SceneTable = TableMgr->GetITTTable<UITTTable_Scene>(UITTTable_Scene::GetTableName()))
		{
			UITTData_SceneCamera* SceneCameraData = SceneTable->GetSceneCameraData(SceneType);

			if (SceneCameraData)
			{
				CameraMgr->SetForceDisableSplitscreen(SceneCameraData->bForceDisableSplitscreen);
			}
		}
	}
}
// ============================ //