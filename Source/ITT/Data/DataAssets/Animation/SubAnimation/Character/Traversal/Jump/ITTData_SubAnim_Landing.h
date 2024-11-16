// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAssets/Animation/SubAnimation/ITTData_SubAnim.h"
#include "ITTData_SubAnim_Landing.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ITT_API UITTData_SubAnim_Landing : public UITTData_SubAnim
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool UseOnlyBasicLanding;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool UseBlendspacesToMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData Landing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData LandingFwd;
  
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData LandingHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData LandingHighFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData CancelLandingHighFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DashLanding;
  
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DashLandingFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData PerfectDashLanding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData PerfectDashLandingFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData StartFromStill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DelayedStart;
  
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData StartFromStillHigh;
  
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData DelayedStartHigh;
  
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData SkyDiveLanding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTAnimSequenceData SkyDiveLandingFwd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData LandingFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData LandingHighFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData DashLandingFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData PerfectDashLandingFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData SkyDiveLandingFwdBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData StartFromStillBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData DelayedStartBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData StartFromStillHighBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FITTBlendSpaceData DelayedStartHighBS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayTimeHigh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_StartFromStill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_DelayedStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_StartFromStillHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_DelayedStartHigh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Blend_CancelLandingHighFwd;
};