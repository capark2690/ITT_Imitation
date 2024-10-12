// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAssets/Animation/SubAnimation/ITTData_SubAnim.h"
#include "ITTData_SubAnim_Jump.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ITT_API UITTData_SubAnim_Jump : public UITTData_SubAnim
{
	GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  bool UseBasicJumpOnly;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData Jump;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData JumpWithSpeedBoost;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData JumpFromLanding;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData JumpFromLandingHigh;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData JumpFwd;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData JumpFwdWithSpeedBoost;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequencesData JumpFwdFromLanding;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequencesData JumpFwdFromLanding_Var2;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData JumpFwdFromLandingHigh;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData Jump180L;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData Jump180R;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData DashJump;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData DashStopJump;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData PerfectDashJump;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData PerfectDashStopJump;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFromLanding_Delay;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFwdFromLanding_Delay;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFromLandingHigh_Delay;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFwdFromLandingHigh_Delay;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFromLandingHigh_Blend;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float JumpFwdFromLandingHigh_Blend;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float Jump180_Blend;
};