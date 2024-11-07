// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ITTPlayerInteractionComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UITTPlayerInteractionComponent();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	
	// ========== Interaction ========== //
	void InputInteraction();

private:
	class IITTInteractableCollisionInterface* GetOverridedInteractionCollision() const;
	// ================================= //
};
