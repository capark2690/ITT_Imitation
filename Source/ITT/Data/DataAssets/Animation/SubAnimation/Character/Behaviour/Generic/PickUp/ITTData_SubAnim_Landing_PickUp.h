// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAssets/Animation/SubAnimation/ITTData_SubAnim.h"
#include "ITTData_SubAnim_Landing_PickUp.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ITT_API UITTData_SubAnim_Landing_PickUp : public UITTData_SubAnim
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData Landing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData LandingFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData LandingHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData StartFromStill;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float blend_StartFromStill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float blend_DelayedStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float blend_StartFromStillHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float blend_DelayedStartHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float blend_CancelLandingHighFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FallTime;
};
