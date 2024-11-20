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
		EITTPlayerCharacterType SelectPlayerCharacterType1 = EITTPlayerCharacterType::None;
		EITTPlayerCharacterType SelectPlayerCharacterType2 = EITTPlayerCharacterType::None;
		
		if (UITTScene_LocalPlay_SelectCharacter* CharacterSelectScene = Cast<UITTScene_LocalPlay_SelectCharacter>(SceneMgr->GetCurrentScene()))
		{
			CharacterSelectScene->GetCharacterSelectState(SelectPlayerCharacterType1, SelectPlayerCharacterType2);
		}
		
		bCharacterSelect_Cody = SelectPlayerCharacterType1 == EITTPlayerCharacterType::Cody;
		bCharacterSelect_May = SelectPlayerCharacterType1 == EITTPlayerCharacterType::May;

		bCharacterSelect_Cody = SelectPlayerCharacterType2 == EITTPlayerCharacterType::Cody ? true : bCharacterSelect_Cody;
		bCharacterSelect_May = SelectPlayerCharacterType2 == EITTPlayerCharacterType::May ? true : bCharacterSelect_May;
	}
}
// ============================================ //