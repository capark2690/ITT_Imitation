// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTSceneBase.h"
#include "Engine/EngineTypes.h"
#include "ITTScene_Ch1_Sequence_PowerSwitchOn.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTScene_Ch1_Sequence_PowerSwitchOn : public UITTSceneBase
{
	GENERATED_BODY()

public:
	UITTScene_Ch1_Sequence_PowerSwitchOn();

	
	virtual void Initialize(EITTSceneType _SceneType) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;


private:
	void PlayLevelSequence();

	UFUNCTION()
	void OnLevelSequenceEndPlay(AActor* Actor , EEndPlayReason::Type Reason);
};
