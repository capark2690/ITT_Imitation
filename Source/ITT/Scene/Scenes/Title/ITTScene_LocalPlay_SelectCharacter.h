﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTSceneBase.h"
#include "Character/ITTDefine_Character.h"
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


public:
	// ========== Character Select State ========== //
	void GetCharacterSelectState(EITTCharacter_Player& OutSelectCharacter_Player1,
	EITTCharacter_Player& OutSelectCharacter_Player2) const;
	// ============================================ //

	
private:
	// ========== Widget ========== //
	TObjectPtr<class UITTWidget_CharacterSelect> Widget_CharacterSelect;
	// ============================ //
};