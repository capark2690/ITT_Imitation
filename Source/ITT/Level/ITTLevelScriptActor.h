// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "ITTLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AITTLevelScriptActor();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
