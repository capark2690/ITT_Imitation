// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAssets/Animation/SubAnimation/ITTData_SubAnim.h"
#include "ITTData_LedgeGrab.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ITT_API UITTData_LedgeGrab : public UITTData_SubAnim
{
	GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData LedgeGrab;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData LedgeHangMh;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTBlendSpaceData MhBlendSpace;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FVector HangOffset;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData LedgeJumpUp;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData LedgeJumpBackLeft;
    
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData LedgeJumpBackRight;
      
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData LedgeDrop;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FITTAnimSequenceData LedgeClimbUp;
};
