// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTActor.h"
#include "ITTActor_Interactable.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTActor_Interactable : public AITTActor
{
	GENERATED_BODY()

public:
	AITTActor_Interactable();
	

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
