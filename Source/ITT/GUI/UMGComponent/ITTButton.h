// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ITTButton.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UITTButton();

	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;

	
public:
	// ========== Text Style ========== //
	virtual void NativeOnCurrentTextStyleChanged() override;
	// ================================ //

	
	// ========== String Index ========== //
	UFUNCTION(Category=ITT, BlueprintCallable)
	void SetStringIndex(int32 _StringIndex);

	UFUNCTION(Category=ITT, BlueprintPure)
	int32 GetStringIndex() const { return StringIndex; }
	
protected:
	void OnChangeStringIndex();
	// ================================== //

	
protected:
	// ========== String Index ========== //
	UPROPERTY(Category=ITT, EditAnywhere, BlueprintGetter=GetStringIndex, BlueprintSetter=SetStringIndex)
	int32 StringIndex;
	// ================================== //


	// ========== BindWidget ========== //
	UPROPERTY(Meta = (BindWidget))
	class UITTTextBlock* TXT_Button;
	// ================================ //
};
