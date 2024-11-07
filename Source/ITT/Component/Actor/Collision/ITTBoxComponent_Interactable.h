// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTBoxComponent.h"
#include "Component/ComponentInterface/Actor/ITTInteractableCollisionInterface.h"
#include "ITTBoxComponent_Interactable.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTBoxComponent_Interactable : public UITTBoxComponent, public IITTInteractableCollisionInterface
{
	GENERATED_BODY()

public:
	UITTBoxComponent_Interactable();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	

	// ========== Interact ========== //
	UFUNCTION()
	virtual void Interact() override;
	// ============================== //
};
