﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTSceneBase.h"
#include "ITTScene_Ch2_Nail.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTScene_Ch2_Nail : public UITTSceneBase
{
	GENERATED_BODY()

public:
	UITTScene_Ch2_Nail();

	
	virtual void Initialize(EITTSceneType _SceneType) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;
};
