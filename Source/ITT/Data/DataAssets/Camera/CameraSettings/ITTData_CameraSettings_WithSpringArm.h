// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTData_CameraSettings.h"
#include "ITTData_CameraSettings_WithSpringArm.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTData_CameraSettings_WithSpringArm : public UITTData_CameraSettings
{
	GENERATED_BODY()

public:
	// SpringArm
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpringArm_TargetArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector SpringArm_TargetOffset;

	
	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator Camera_Rotator;
};
