// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTSceneBase.h"
#include "Engine/EngineTypes.h"
#include "ITTScene_FullScreenSequence.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTScene_FullScreenSequence : public UITTSceneBase
{
	GENERATED_BODY()

public:
	UITTScene_FullScreenSequence();

	
	virtual void Initialize(EITTSceneType _SceneType, struct FITTTableRow_Scene* _SceneRow) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;


protected:
	// ========== Sequence ========== //
	void PlayLevelSequence();

	UFUNCTION()
	void OnStopLevelSequence();
	// ============================== //


protected:
	// ========== Sequence ========== //
	FName SequenceName;
	// ============================== //
};
