// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTScene_FullScreenSequence.h"
#include "ITTScene_Ch1_PowerSwitchOn.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTScene_Ch1_PowerSwitchOn : public UITTScene_FullScreenSequence
{
	GENERATED_BODY()

public:
	UITTScene_Ch1_PowerSwitchOn();

	
	virtual void Initialize(EITTSceneType _SceneType, struct FITTTableRow_Scene* _SceneRow) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;
};
