// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTSceneBase.h"
#include "ITTScene_LocalPlay_SelectCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTScene_LocalPlay_SelectCharacter : public UITTSceneBase
{
	GENERATED_BODY()

public:
	UITTScene_LocalPlay_SelectCharacter();

	
	virtual void Initialize(EITTSceneType _SceneType) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

	
private:
	// ========== Widget ========== //
	void CreateWidget();
	// ============================ //


	// ========== Camera ========== //
	void SetTargetCamera();
	// ============================ //

	
private:
	// ========== Widget ========== //
	TObjectPtr<class UITTWidget_CharacterSelect> Widget_CharacterSelect;
	// ============================ //
};
