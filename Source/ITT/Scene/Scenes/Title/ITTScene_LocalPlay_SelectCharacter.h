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

	
	virtual void Initialize(EITTSceneType _SceneType, struct FITTTableRow_Scene* _SceneRow) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

	
private:
	// ========== Widget ========== //
	void CreateWidget();
	// ============================ //


public:
	// ========== Character Select State ========== //
	void BindToCharacterSelectWidget();

	void OnChangeCharacterSelectState(EITTPlayerCharacterType SelectedPlayerCharacterType1,
		EITTPlayerCharacterType SelectedPlayerCharacterType2);
	
	void GetCharacterSelectState(EITTPlayerCharacterType& OutSelectCharacter_Player1,
		EITTPlayerCharacterType& OutSelectCharacter_Player2) const;
	// ============================================ //

	
private:
	static constexpr char ActorKey_CharacterSelect[] = "BP_Rose_CharacterSelect";
	static constexpr char ComponentTag_CharacterSelectMesh[] = "CharacterSelectMesh";

	
	// ========== Widget ========== //
	TObjectPtr<class UITTWidget_CharacterSelect> Widget_CharacterSelect;
	// ============================ //
};