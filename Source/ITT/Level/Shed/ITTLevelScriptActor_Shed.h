// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/ITTLevelScriptActor.h"
#include "ITTLevelScriptActor_Shed.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTLevelScriptActor_Shed : public AITTLevelScriptActor
{
	GENERATED_BODY()

public:
	AITTLevelScriptActor_Shed();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
