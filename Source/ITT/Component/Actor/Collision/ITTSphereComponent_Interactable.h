// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTSphereComponent.h"
#include "Component/ComponentInterface/Actor/ITTInteractionInputInterface.h"
#include "ITTSphereComponent_Interactable.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTSphereComponent_Interactable : public UITTSphereComponent, public IITTInteractionInput
{
	GENERATED_BODY()

public:
	UITTSphereComponent_Interactable();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	
	// ========== Interact ========== //
	virtual void InputInteract(class AITTCharacterBase* InteractorCharacter) override;
	// ============================== //
};
