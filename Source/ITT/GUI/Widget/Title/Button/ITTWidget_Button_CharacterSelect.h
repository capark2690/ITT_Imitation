// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "ITTWidget_Button_CharacterSelect.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidget_Button_CharacterSelect : public UITTWidget
{
	GENERATED_BODY()

public:
	UITTWidget_Button_CharacterSelect(const FObjectInitializer& ObjectInitializer);

	
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


	// ========== Player ========== //
	void SetControllerId(uint8 _ControllerId);
	// ============================= //

	
private:
	// ========== Design ========== //
	void InitializeDesign();

	void SetKeyImageByPlayerId();

public:
	void SetConfirmWidgetSwitcher(bool bConfirm);
	// ============================ //

	
protected:
	// ========== Player ========== //
	UPROPERTY(Category=ITT, EditInstanceOnly)
	uint8 ControllerId;
	// ============================= //

	
	// ========== UMG ========== //
	UPROPERTY(Meta = (BindWidget))
	class UImage* IMG_Bg;
	
	UPROPERTY(Meta = (BindWidget))
	class UCommonTextBlock* TXT_UserName;
	
	UPROPERTY(Meta = (BindWidget))
	class UImage* IMG_Device;
	
	UPROPERTY(Meta = (BindWidget))
	class UImage* IMG_Arrow_R;
	
	UPROPERTY(Meta = (BindWidget))
	class UImage* IMG_Arrow_L;

	UPROPERTY(Meta = (BindWidget))
	class UWidgetSwitcher* WS_Confirm;
	
	UPROPERTY(Meta = (BindWidget))
	class UVerticalBox* VBX_Confirm;

	UPROPERTY(Meta = (BindWidget))
	class UITTWidget_Key* WBP_ConfirmKey;
	// ========================= //

	
	// ========== Default ========== //
	UPROPERTY(Category=ITT, EditInstanceOnly)
	bool bIsSelectBTN;

	UPROPERTY(Category=ITT, EditInstanceOnly)
	FSlateColor BgColor;
	// ============================= //

	
	// ========== Design ========== //
	UPROPERTY(Category=ITT, EditDefaultsOnly)
	FSlateBrush SlateBrush_Keyboard;

	UPROPERTY(Category=ITT, EditDefaultsOnly)
	FSlateBrush SlateBrush_Gamepad;
	// ============================ //
};
