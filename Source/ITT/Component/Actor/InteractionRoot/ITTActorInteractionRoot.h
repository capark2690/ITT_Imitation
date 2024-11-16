// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ITTActorInteractionRoot.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTActorInteractionRoot : public USceneComponent
{
	GENERATED_BODY()

public:
	UITTActorInteractionRoot();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
