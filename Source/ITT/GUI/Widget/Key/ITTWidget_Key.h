// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "ITTWidget_Key.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidget_Key : public UITTWidget
{
	GENERATED_BODY()

public:
	UITTWidget_Key(const FObjectInitializer& ObjectInitializer);

	
	virtual void NativeConstruct() override;


	// ========== Key ========== //
	void UpdateKeyImage(int8 ControllerId);
	// ========================= //

	
	// ==================== Getter / Setter ==================== //
	// ========== Key ========== //
	UFUNCTION(Category=ITT, BlueprintCallable)
	void SetKey(const FKey& _Key_Keyboard, const FKey& _Key_Gamepad);
	// ========================= //
	// ========================================================= //

	
protected:
	// ========== Default ========== //
	UPROPERTY(Category=ITT, EditInstanceOnly)
	FKey Key_Keyboard;
	
	UPROPERTY(Category=ITT, EditInstanceOnly)
	FKey Key_Gamepad;
	// ============================= //

	
	// ========== UMG ========== //
	UPROPERTY(Meta = (BindWidget))
	class UImage* IMG_Bg;
	
	UPROPERTY(Meta = (BindWidget))
	class UImage* IMG_Key;

	UPROPERTY(Meta = (BindWidget))
	class UCommonTextBlock* TXT_Key;
	// ========================= //
};
