// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_Button_CharacterSelect.h"

#include "Components/Image.h"
#include "Components/VerticalBox.h"

#include "GUI/Widget/Key/ITTWidget_Key.h"


UITTWidget_Button_CharacterSelect::UITTWidget_Button_CharacterSelect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), ControllerId(0)
{
}


void UITTWidget_Button_CharacterSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UITTWidget_Button_CharacterSelect::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UITTWidget_Button_CharacterSelect::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeDesign();
}

void UITTWidget_Button_CharacterSelect::NativeDestruct()
{
	Super::NativeDestruct();
}


// ========== Player ========== //
void UITTWidget_Button_CharacterSelect::SetControllerId(uint8 _ControllerId)
{
	ControllerId = _ControllerId;
	
	SetKeyImageByPlayerId();
}
// ============================= //


// ========== Design ========== //
void UITTWidget_Button_CharacterSelect::InitializeDesign()
{
	VBX_Confirm->SetVisibility(bIsSelectBTN ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);

	IMG_Bg->SetBrushTintColor(BgColor);

	SetKeyImageByPlayerId();
}

void UITTWidget_Button_CharacterSelect::SetKeyImageByPlayerId()
{
	if (ControllerId == 0)
	{
		IMG_Device->SetBrush(SlateBrush_Keyboard);

		WBP_ConfirmKey->UpdateKeyImage(ControllerId);
	}
	
	if (ControllerId == 1)
	{
		IMG_Device->SetBrush(SlateBrush_Gamepad);

		WBP_ConfirmKey->UpdateKeyImage(ControllerId);
	}
}
// ============================ //