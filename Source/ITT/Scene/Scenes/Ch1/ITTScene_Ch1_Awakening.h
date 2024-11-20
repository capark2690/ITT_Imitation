// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTSceneBase.h"
#include "ITTScene_Ch1_Awakening.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTScene_Ch1_Awakening : public UITTSceneBase
{
	GENERATED_BODY()

public:
	UITTScene_Ch1_Awakening();

	
	virtual void Initialize(EITTSceneType _SceneType, struct FITTTableRow_Scene* _SceneRow) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;
};
