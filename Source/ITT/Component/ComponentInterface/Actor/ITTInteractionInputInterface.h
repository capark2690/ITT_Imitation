// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITTInteractionInputInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UITTInteractionInput : public UInterface
{
	GENERATED_BODY()
};


class ITT_API IITTInteractionInput
{
	GENERATED_BODY()

public:
	// ========== Interact ========== //
	UFUNCTION()
	virtual void InputInteract(class AITTCharacterBase* InteractorCharacter);
	// ============================== //
};