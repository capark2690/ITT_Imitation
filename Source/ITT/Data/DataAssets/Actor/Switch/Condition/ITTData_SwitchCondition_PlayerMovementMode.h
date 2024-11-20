// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTData_SwitchCondition.h"
#include "Character/ITTDefine_Character.h"
#include "ITTData_SwitchCondition_PlayerMovementMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ITT_API UITTData_SwitchCondition_PlayerMovementMode : public UITTData_SwitchCondition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EITTPlayerCharacterType TargetPlayerCharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FITTMovementMode> MovementModes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bInclude;
};
