// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ITTData_SwitchCondition.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTData_SwitchCondition : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EITTSwitchConditionTriggerType ConditionTriggerType;
};
