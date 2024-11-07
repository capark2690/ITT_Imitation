// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITTCollisionBaseInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UITTCollisionBaseInterface : public UInterface
{
	GENERATED_BODY()
};


class ITT_API IITTCollisionBaseInterface
{
	GENERATED_BODY()

public:
	// ========== Priority ========== //
	UFUNCTION()
	virtual int32 GetPriority();
	// ============================== //
};