// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTSceneBase.h"
#include "ITTScene_ProductionLogo.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTScene_ProductionLogo : public UITTSceneBase
{
	GENERATED_BODY()

public:
	UITTScene_ProductionLogo();

	
	virtual void Initialize(EITTSceneType _SceneType) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;


private:
	// ========== Widget ========== //
	void CreateWidget();
	void DestroyWidget();
	// ============================ //
};