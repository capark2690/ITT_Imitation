// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTTable_Scene.h"

#include "ITTUtilityFunctionLibrary.h"


UITTTable_Scene::UITTTable_Scene()
{
}


void UITTTable_Scene::Initialize()
{
	Super::Initialize();

	ITTCHECK(GetDataTable());

	EntireSceneTypes.Empty();
	SceneTypeToRow.Empty();
	
	TArray<FITTTableRow_Scene*> Rows;
	GetDataTable()->GetAllRows<FITTTableRow_Scene>(ITTTEXT_FUNC, Rows);

	for (FITTTableRow_Scene* Row : Rows)
	{
		if (EntireSceneTypes.Contains(Row->SceneType))
		{
			FString SceneTypeName = UITTUtilityFunctionLibrary::ConvertEnumToString(TEXT("EITTSceneType"), Row->SceneType);
			ITTENSUREF(false, TEXT("[%s] The same SceneType already contained [SceneType : %s]")
				, *ITTSTRING_FUNC, *SceneTypeName);
		}
		
		EntireSceneTypes.Emplace(Row->SceneType);
		
		SceneTypeToRow.Emplace(Row->SceneType, *Row);
	}
}


// ========== Scene ========== //
FITTTableRow_Scene* UITTTable_Scene::GetSceneRow(EITTSceneType SceneType)
{
	if (!SceneTypeToRow.Contains(SceneType))
	{
		FString SceneTypeName = UITTUtilityFunctionLibrary::ConvertEnumToString(TEXT("EITTSceneType"), static_cast<uint32>(SceneType));
		ITTLOG(Error, TEXT("[%s] SceneType doesn't exist in SceneTypeToRow [SceneType : %s]"), *ITTSTRING_FUNC, *SceneTypeName);
	}

	return SceneTypeToRow.Find(SceneType);
}
// =========================== //
