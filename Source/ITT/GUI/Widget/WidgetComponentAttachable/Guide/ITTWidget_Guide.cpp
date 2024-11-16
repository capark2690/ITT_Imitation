// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_Guide.h"

#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"


UITTWidget_Guide::UITTWidget_Guide(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UITTWidget_Guide::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeDesign();
}


// ========== Widget Component ========== //
void UITTWidget_Guide::OnActiveWidgetComponent(int32 StateId)
{
	WS_Guide->SetActiveWidgetIndex(StateId);
}

void UITTWidget_Guide::OnDeactiveWidgetComponent()
{
}
// ============================== //


// ========== Design ========== //
void UITTWidget_Guide::InitializeDesign()
{
	IMG_Bg->SetBrushTintColor(BgColor);
}
// ============================ //