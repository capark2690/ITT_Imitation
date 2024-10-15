// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "ITTWidget_EditorHUD_LocalMultiplay.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidget_EditorHUD_LocalMultiplay : public UITTWidget
{
	GENERATED_BODY()

public:
	UITTWidget_EditorHUD_LocalMultiplay(const FObjectInitializer& ObjectInitializer);

	
	virtual void NativeOnInitialized() override;
};
