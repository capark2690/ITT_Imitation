// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTActorInteractionRoot.h"
#include "ITTActorInteractionRoot_FuseCrab.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTActorInteractionRoot_FuseCrab : public UITTActorInteractionRoot
{
	GENERATED_BODY()

public:
	UITTActorInteractionRoot_FuseCrab();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// ========== Interact ========== //
	virtual void Interact(class AITTCharacterBase* Interactor) override;
	
	virtual void StopInteract() override;
	// ============================== //
};
