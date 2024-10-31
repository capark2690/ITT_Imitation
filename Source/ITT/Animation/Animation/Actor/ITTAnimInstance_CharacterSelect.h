// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/Animation/ITTAnimInstance.h"
#include "Character/ITTDefine_Character.h"
#include "ITTAnimInstance_CharacterSelect.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTAnimInstance_CharacterSelect : public UITTAnimInstance
{
	GENERATED_BODY()

public:
	UITTAnimInstance_CharacterSelect();

	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


protected:
	// ========== Character Select State ========== //
	virtual void UpdateCharacterSelectState();
	// ============================================ //


protected:
	// ========== Character Select State ========== //
	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly)
	bool bCharacterSelect_Cody;

	UPROPERTY(Category = ITTAnim, VisibleAnywhere, BlueprintReadOnly)
	bool bCharacterSelect_May;
	// ============================================ //
};
