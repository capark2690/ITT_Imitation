// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAssets/Animation/SubAnimation/ITTData_SubAnim.h"
#include "ITTData_SubAnim_Dash.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ITT_API UITTData_SubAnim_Dash : public UITTData_SubAnim
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool UseBlendspacesToMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DashStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DashStop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DashToJog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DashToAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DashFromLongJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DashFromGroundPound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData DashToJogBS;
};
