// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ITTActor.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTActor : public AActor
{
	GENERATED_BODY()

public:
	AITTActor();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};