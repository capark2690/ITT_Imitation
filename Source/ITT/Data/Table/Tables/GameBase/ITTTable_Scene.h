// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Table/ITTTableBase.h"
#include "Engine/DataTable.h"
#include "Templates/SubclassOf.h"
#include "GameBase/ITTDefine_GameBase.h"
#include "ITTTable_Scene.generated.h"

/**
 * 
 */
USTRUCT()
struct FITTTableRow_Scene : public FTableRowBase
{
	GENERATED_BODY()

	FITTTableRow_Scene()
		: SceneType(EITTSceneType::None), ITTSceneClass(nullptr), LevelName(FName())
	{
	}

	UPROPERTY(EditAnywhere)
	EITTSceneType SceneType;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UITTSceneBase> ITTSceneClass;

	UPROPERTY(EditAnywhere)
	FName LevelName;

	UPROPERTY(EditAnywhere)
	EITTSceneType DefaultNextSceneType;
	
	UPROPERTY(EditAnywhere)
	class UITTData_SceneCamera* SceneCameraData;
};


UCLASS()
class ITT_API UITTTable_Scene : public UITTTableBase
{
	GENERATED_BODY()
	
public:
	static FName GetTableName() { return FName(TableName); }

	
	UITTTable_Scene();

	
	virtual void Initialize() override;


	// ========== Scene ========== //
	const TArray<EITTSceneType>& GetEntireSceneTypes() const { return EntireSceneTypes; }

	FITTTableRow_Scene* GetSceneRow(EITTSceneType SceneType);
	// =========================== //
	
	
private:
	static constexpr char TableName[] = "DT_Scene";

	
	// ========== Scene ========== //
	UPROPERTY()
	TArray<EITTSceneType> EntireSceneTypes;

	UPROPERTY()
	TMap<EITTSceneType, FITTTableRow_Scene> SceneTypeToRow;
	// =========================== //
};