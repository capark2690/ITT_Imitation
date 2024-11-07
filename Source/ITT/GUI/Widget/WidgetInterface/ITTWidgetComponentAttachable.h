// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITTWidgetComponentAttachable.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UITTWidgetComponentAttachable : public UInterface
{
	GENERATED_BODY()
};


class ITT_API IITTWidgetComponentAttachable
{
	GENERATED_BODY()

public:
	// ========== Widget Component ========== //
	UFUNCTION()
	virtual void OnActiveWidgetComponent(int32 StateId);
	
	UFUNCTION()
	virtual void OnDeactiveWidgetComponent();
	// ============================== //
};