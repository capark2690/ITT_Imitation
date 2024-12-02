// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTAnimInstance_CharacterSelect.h"

#include "Character/ITTDefine_Character.h"


UITTAnimInstance_CharacterSelect::UITTAnimInstance_CharacterSelect()
	: bCharacterSelect_Cody(false), bCharacterSelect_May(false)
{
}


void UITTAnimInstance_CharacterSelect::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UITTAnimInstance_CharacterSelect::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}


// ========== Character Select State ========== //
void UITTAnimInstance_CharacterSelect::UpdateCharacterSelectState(EITTPlayerCharacterType SelectPlayerCharacterType1, EITTPlayerCharacterType SelectPlayerCharacterType2)
{
	bCharacterSelect_Cody = SelectPlayerCharacterType1 == EITTPlayerCharacterType::Cody;
	bCharacterSelect_May = SelectPlayerCharacterType1 == EITTPlayerCharacterType::May;

	bCharacterSelect_Cody = SelectPlayerCharacterType2 == EITTPlayerCharacterType::Cody ? true : bCharacterSelect_Cody;
	bCharacterSelect_May = SelectPlayerCharacterType2 == EITTPlayerCharacterType::May ? true : bCharacterSelect_May;
}
// ============================================ //