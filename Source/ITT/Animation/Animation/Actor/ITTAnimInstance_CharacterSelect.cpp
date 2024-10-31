// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTAnimInstance_CharacterSelect.h"

#include "GameBase/GameManager/GameBase/ITTSceneManager.h"
#include "Scene/Scenes/Title/ITTScene_LocalPlay_SelectCharacter.h"


UITTAnimInstance_CharacterSelect::UITTAnimInstance_CharacterSelect()
{
}


void UITTAnimInstance_CharacterSelect::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UITTAnimInstance_CharacterSelect::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateCharacterSelectState();
}


// ========== Character Select State ========== //
void UITTAnimInstance_CharacterSelect::UpdateCharacterSelectState()
{
	if (SceneMgr)
	{
		EITTCharacter_Player SelectCharacter_Player1 = EITTCharacter_Player::None;
		EITTCharacter_Player SelectCharacter_Player2 = EITTCharacter_Player::None;
		
		if (UITTScene_LocalPlay_SelectCharacter* CharacterSelectScene = Cast<UITTScene_LocalPlay_SelectCharacter>(SceneMgr->GetCurrentScene()))
		{
			CharacterSelectScene->GetCharacterSelectState(SelectCharacter_Player1, SelectCharacter_Player2);
		}
		
		bCharacterSelect_Cody = SelectCharacter_Player1 == EITTCharacter_Player::Cody;
		bCharacterSelect_May = SelectCharacter_Player1 == EITTCharacter_Player::May;

		bCharacterSelect_Cody = SelectCharacter_Player2 == EITTCharacter_Player::Cody ? true : bCharacterSelect_Cody;
		bCharacterSelect_May = SelectCharacter_Player2 == EITTCharacter_Player::May ? true : bCharacterSelect_May;
	}
}
// ============================================ //