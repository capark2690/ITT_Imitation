// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "Character/ITTDefine_Character.h"
#include "ITTWidget_CharacterSelect.generated.h"

/**
 * 
 */
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

	
	// ========== Input Action ========== //
	void BindInputAction();
	
	void ClearInputActionBindings();
	// ================================== //


private:
	// ========== Input ========== //
	// -- Keyboard -- //
	void InputConfirm_Keyboard();
	void InputStopConfirm_Keyboard();
	
	void InputRight_Keyboard();
	
	void InputLeft_Keyboard();


	// -- Gamepad -- //
	void InputConfirm_Gamepad();
	void InputStopConfirm_Gamepad();
	
	void InputRight_Gamepad();
	
	void InputLeft_Gamepad();
	// =========================== //


	// ========== Progress ========== //
	void ResetConfirm();
	
	void CalcConfirmTime(float InDeltaTime);

	void CheckConfirm();
	// ============================== //

	
	// ========== Design ========== //
	void UpdateDesign_BTN();
	// ============================ //

	
protected:
	static constexpr char ClassWidgetKey[] = "WBP_CharacterSelect";
	
	
	// ========== Input Action ========== //
	// -- Keyboard -- //
	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ConfirmAction_Keyboard;
	
	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RightAction_Keyboard;

	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftAction_Keyboard;

	
	// -- Gamepad -- //
	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ConfirmAction_Gamepad;
	
	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RightAction_Gamepad;

	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftAction_Gamepad;
	// ================================== //


	// ========== Progress ========== //
	EITTCharacter_Player SelectCharacter_Player1;
	EITTCharacter_Player SelectCharacter_Player2;

	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxConfirmTime;
	
	float ConfirmTime_Player1;
	float ConfirmTime_Player2;

	bool bInputConfirm_Player1;
	bool bInputConfirm_Player2;
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
	// ========================= //
};
// ToDo : Processing when using the same controller device