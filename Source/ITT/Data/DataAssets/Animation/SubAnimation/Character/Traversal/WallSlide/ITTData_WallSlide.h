// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAssets/Animation/SubAnimation/ITTData_SubAnim.h"
#include "ITTData_WallSlide.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ITT_API UITTData_WallSlide : public UITTData_SubAnim
{
	GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData WallSlide;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData WallSlideReadyToDash;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData WallJump;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData WallJumpHorizontal;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData IntoWallSlide;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData IntoWallSlideFromDash;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData IntoWallSlideNotJumpableStart;
};
