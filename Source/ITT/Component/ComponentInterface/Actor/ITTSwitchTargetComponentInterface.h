// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITTSwitchTargetComponentInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UITTSwitchTargetComponentInterface : public UInterface
{
	GENERATED_BODY()
};


class ITT_API IITTSwitchTargetComponentInterface
{
	GENERATED_BODY()

public:
	// ========== Active Component ========== //
	UFUNCTION()
	virtual void ActiveComponent(bool bResetCount = true);

	UFUNCTION()
	virtual void DeactiveComponent();
	// ====================================== //
};