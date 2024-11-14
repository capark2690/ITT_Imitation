// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/UMGComponent/ITTButton.h"
#include "ITTButton_WithKey.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTButton_WithKey : public UITTButton
{
	GENERATED_BODY()

public:
	UITTButton_WithKey();


	void NativeOnInitialized() override;

	
private:
	// ========== Key ========== //
	void UpdateKeyImage();
	// ========================= //

	
protected:
	// ========== Key ========== //
	UPROPERTY(Category=ITT, EditInstanceOnly)
	FKey Key_Keyboard;
	
	UPROPERTY(Category=ITT, EditInstanceOnly)
	FKey Key_Gamepad;

	
	UPROPERTY(Meta = (BindWidget))
	class UITTWidget_Key* WBP_Key;
	// ========================= //
};
