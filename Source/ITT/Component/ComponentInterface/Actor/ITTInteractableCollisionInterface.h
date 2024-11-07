﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITTCollisionBaseInterface.h"
#include "ITTInteractableCollisionInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UITTInteractableCollisionInterface : public UInterface
{
	GENERATED_BODY()
};


class ITT_API IITTInteractableCollisionInterface
{
	GENERATED_BODY()

public:
	// ========== Interact ========== //
	UFUNCTION()
	virtual void Interact();
	// ============================== //
};