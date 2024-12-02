// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameBase/ITTDefine_GameBase.h"
#include "ITTSceneBase.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTSceneBase : public UObject
{
	GENERATED_BODY()

public:
	UITTSceneBase();

	
	virtual void Initialize(EITTSceneType _SceneType, struct FITTTableRow_Scene* _SceneRow);
	virtual void Finalize();
	virtual void Tick(float DeltaTime);

	
	// ========== Finish ========== //
	virtual void PrepareToFinish(EITTSceneType NextSceneType, EITTLoadingType LoadingType);
	virtual void PrepareToFinish_Immediately(EITTSceneType NextSceneType, EITTLoadingType LoadingType);
	
	virtual void TransferData(TObjectPtr<UITTSceneBase>& NextScene) {}
	// ============================ //

	
	// ========== Scene ========== //
	EITTSceneType GetSceneType() const { return SceneType; }
	// =========================== //


protected:
	// ========== Camera ========== //
	void SetSceneCamera();
	// ============================ //

	
protected:
	// ========== Scene ========== //
	EITTSceneType SceneType;

	struct FITTTableRow_Scene* SceneRow;
	// =========================== //

	
public:
	// ==================== Delegate ==================== //
	// ========== Finish ========== //
	FITTOnReadyToFinishDelegate OnReadyToFinishDelegate;
	// ============================ //
	// ================================================== //
};