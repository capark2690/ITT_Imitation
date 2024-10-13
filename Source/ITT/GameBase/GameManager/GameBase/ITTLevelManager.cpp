// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTLevelManager.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "GameBase/BasicUtility/ITTBasicUtility.h"
#include "GameBase/GameManager/Data/ITTTableManager.h"
#include "Data/Table/Tables/GameBase/ITTTable_Level.h"


UITTLevelManager::UITTLevelManager()
{
}


// ========== Open Level ========== //
bool UITTLevelManager::OpenLevelByTable(const FITTOnLoadLevelComplete& Delegate, const FName& LevelName)
{
	if (TableMgr)
	{
		const FName& LevelTableName = UITTTable_Level::GetTableName();
		UITTTable_Level* ITTTable_Level = TableMgr->GetITTTable<UITTTable_Level>(LevelTableName);
		ITTCHECK(IsValid(ITTTable_Level));

		const TSoftObjectPtr<UWorld>& LevelSoftObject = ITTTable_Level->GetSoftObject(LevelName);
		if (OpenLevelBySoftObjectPtr(Delegate, LevelSoftObject))
		{
			CurrentLevelName = LevelName;
			return true;
		}
	
		const FName& LevelPath = ITTTable_Level->GetLevelPath(LevelName);
		if (!LevelName.IsNone())
		{
			if (OpenLevelByPath(Delegate, LevelPath))
			{
				CurrentLevelName = LevelName;
				return true;
			}
		}
	}
	
	return false;
}

bool UITTLevelManager::OpenLevelByPath(const FITTOnLoadLevelComplete& Delegate, const FName& LevelPath, bool bAbsolute)
{
	UWorld* World = UITTBasicUtility::GetITTWorld();
	if(World == nullptr)
	{
		return false;
	}

	UGameplayStatics::OpenLevel(World, LevelPath, bAbsolute);

	if (OnLoadLevelComplete.IsBound())
	{
		OnLoadLevelComplete.Unbind();
	}
	OnLoadLevelComplete = Delegate;

	return true;
}

bool UITTLevelManager::OpenLevelBySoftObjectPtr(const FITTOnLoadLevelComplete& Delegate, const TSoftObjectPtr<UWorld>& LevelSoftObject, bool bAbsolute)
{
	UWorld* World = UITTBasicUtility::GetITTWorld();
	if(World == nullptr)
	{
		return false;
	}
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(World, LevelSoftObject, bAbsolute);

	if (OnLoadLevelComplete.IsBound())
	{
		OnLoadLevelComplete.Unbind();
	}
	OnLoadLevelComplete = Delegate;

	return true;
}
// ================================ //


// ========== Complete ========== //
void UITTLevelManager::LoadLevelComplete()
{
	bool bDelegateBound = OnLoadLevelComplete.ExecuteIfBound(FString());
	if (!bDelegateBound)
	{
		ITTLOG(Log, TEXT("[%s] OnLoadLevelComplete isn't bound"), *ITTSTRING_FUNC);
	}
}
// ============================== //