﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "GameBase/ITTDefine_GameBase.h"
#include "Character/ITTDefine_Character.h"
#include "ITTWidget_CharacterSelect.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_TwoParams(FITTOnChangeCharacterSelectStateDelegate, EITTPlayerCharacterType, EITTPlayerCharacterType);


UCLASS()
class ITT_API UITTWidget_CharacterSelect : public UITTWidget
{
	GENERATED_BODY()

public:
	static FName GetClassWidgetKey() { return FName(ClassWidgetKey); }

	
	UITTWidget_CharacterSelect(const FObjectInitializer& ObjectInitializer);
	

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


protected:
	// ========== Close ========== //
	virtual void PrepareToFinish() override;
	
	virtual void Finish() override;
	// =========================== //


	// ========== Button ========== //
	void BindButtons();

	
	UFUNCTION()
	void OnClickButton_Back();
	// ============================ //
	
	
	// ========== Input Action ========== //
	void BindInputAction();
	
	void ClearInputActionBindings();
	// ================================== //


private:
	// ========== Input ========== //
	// -- Player1 -- //
	void InputConfirm_Player1();
	
	void InputRight_Player1();
	
	void InputLeft_Player1();


	// -- Player2 -- //
	void InputConfirm_Player2();
	
	void InputRight_Player2();
	
	void InputLeft_Player2();


	// -- Both -- //
	void InputBack();
	// =========================== //


	// ========== Progress ========== //
	void CheckConfirm();
	// ============================== //

	
	// ========== Design ========== //
	void UpdateDesign_BTN();
	// ============================ //


public:
	// ========== Widget Animation ========== //
	void PlayDisappearanceWidgetAnimation();

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
	// ====================================== //

	
	// ========== Character Select State ========== //
	void OnChangeCharacterSelectState();
	
	void GetCharacterSelectState(EITTPlayerCharacterType& OutSelectPlayerCharacterType1, EITTPlayerCharacterType& OutSelectPlayerCharacterType2) const;
	// ============================================ //
	
	
private:
	static constexpr char ClassWidgetKey[] = "WBP_CharacterSelect";

	
	EITTSceneType NextSceneType;

	
	// ========== Input Action ========== //
	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ConfirmAction;
	
	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RightAction;

	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftAction;

	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BackAction;
	// ================================== //


	// ========== Progress ========== //
	EITTPlayerCharacterType SelectedPlayerCharacterType1;
	EITTPlayerCharacterType SelectedPlayerCharacterType2;
	
	bool bConfirm_Player1;
	bool bConfirm_Player2;
	// ============================== //


	// ========== UMG ========== //
	UPROPERTY(Meta = (BindWidget))
	class UITTWidget_Button_CharacterSelect* WBP_SelectBTN_Player1;
	
	UPROPERTY(Meta = (BindWidget))
	class UITTWidget_Button_CharacterSelect* WBP_SelectBTN_Player2;
	
	UPROPERTY(Meta = (BindWidget))
	class UITTWidget_Button_CharacterSelect* WBP_ConfirmBTN_Left;
	
	UPROPERTY(Meta = (BindWidget))
	class UITTWidget_Button_CharacterSelect* WBP_ConfirmBTN_Right;

	UPROPERTY(Meta = (BindWidget))
	class UITTButton_WithKey* BTN_Back;
	// ========================= //

	
	// ========== Widget Animation ========== //
	bool bWAnimFinished;
	
	UPROPERTY(Transient, Meta = (BindWidgetAnim))
	class UWidgetAnimation* WAnim_Disappearance;
	// ====================================== //

	
public:
	// ==================== Delegate ==================== //
	// ========== Interact ========== //
	FITTOnChangeCharacterSelectStateDelegate OnChangeCharacterSelectStateDelegate;
	// ============================== //
	// ================================================== //
};
// ToDo : Processing when using the same controller device