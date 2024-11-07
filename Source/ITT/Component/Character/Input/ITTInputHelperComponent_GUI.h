// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ITTInputHelperComponent_GUI.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTInputHelperComponent_GUI : public UActorComponent
{
	GENERATED_BODY()

public:
	UITTInputHelperComponent_GUI();

	
protected:
	virtual void BeginPlay() override;


public:
	// ========== Input ========== //
	virtual void SetupPlayerInputComponent(class UInputComponent* _PlayerInputComponent);
	// =========================== //
	
	
private:
	// ========== Input ========== //
	UPROPERTY(Category = ITT, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;
	// =========================== //
};
