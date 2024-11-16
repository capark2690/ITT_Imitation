// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "GUI/Widget/WidgetInterface/ITTWidgetComponentAttachable.h"
#include "ITTWidget_Guide.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidget_Guide : public UITTWidget, public IITTWidgetComponentAttachable
{
	GENERATED_BODY()

public:
	UITTWidget_Guide(const FObjectInitializer& ObjectInitializer);


	virtual void NativeOnInitialized() override;

	
	// ========== Widget Component ========== //
	UFUNCTION()
	virtual void OnActiveWidgetComponent(int32 StateId);
	
	UFUNCTION()
	virtual void OnDeactiveWidgetComponent();
	// ============================== //


private:
	// ========== Design ========== //
	void InitializeDesign();
	// ============================ //

	
protected:
	// ========== Design ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	FSlateColor BgColor;
	// ============================ //


	// ========== UMG ========== //
	UPROPERTY(Meta = (BindWidget))
	class UImage* IMG_Bg;
	
	UPROPERTY(Meta = (BindWidget))
	class UWidgetSwitcher* WS_Guide;
	// ========================= //
};
