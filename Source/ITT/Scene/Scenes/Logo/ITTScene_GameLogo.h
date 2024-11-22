// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTSceneBase.h"
#include "ITTScene_GameLogo.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTScene_GameLogo : public UITTSceneBase
{
	GENERATED_BODY()

public:
	UITTScene_GameLogo();

	
	virtual void Initialize(EITTSceneType _SceneType, struct FITTTableRow_Scene* _SceneRow) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;


protected:
	// ========== Widget ========== //
	void CreateWidget();
	void DestroyWidget();
	// ============================ //


protected:
	// ========== Widget ========== //
	TObjectPtr<class UITTWidget> Widget;
	// ============================ //
};