// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTButton_WithKey.h"

#include "GUI/Widget/Key/ITTWidget_Key.h"


UITTButton_WithKey::UITTButton_WithKey()
{
}


void UITTButton_WithKey::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UpdateKeyImage();
}


// ========== Key ========== //
void UITTButton_WithKey::UpdateKeyImage()
{
	WBP_Key->SetKey(Key_Keyboard, Key_Gamepad);
}
// ========================= //