// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAssets/Animation/SubAnimation/ITTData_SubAnim.h"
#include "ITTData_SubAnim_Movement_PickUp.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ITT_API UITTData_SubAnim_Movement_PickUp : public UITTData_SubAnim
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequencesData IdleAnimations;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData StopAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequencesData Movement;
};
