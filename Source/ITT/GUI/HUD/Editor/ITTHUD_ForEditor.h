// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/HUD/ITTHUD.h"
#include "ITTHUD_ForEditor.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTHUD_ForEditor : public AITTHUD
{
	GENERATED_BODY()

public:
	AITTHUD_ForEditor(const FObjectInitializer& ObjectInitializer);

    
protected:
	// ========== Hud Widget ========== //
	virtual void CreateHudWidgets() override;
	virtual void CloseHudWidgets() override;
    
public:
	virtual void ChangeHudActivation(const FName& HudKey, bool bActive) override;
	// ================================ //

	
protected:
	// ========== Hud Widget ========== //
#if WITH_EDITORONLY_DATA
	UPROPERTY(Category=ITT, EditAnywhere)
	TMap<TSubclassOf<class UITTWidget>, bool> HudWidgetClassToDefalutActivation;
#endif
	// ================================ //
};
