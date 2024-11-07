// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/ComponentInterface/Actor/ITTSwitchTargetComponentInterface.h"
#include "Actor/ITTDefine_Actor.h"
#include "ITTRotationComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTRotationComponent : public UActorComponent, public IITTSwitchTargetComponentInterface
{
	GENERATED_BODY()

public:
	UITTRotationComponent();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	// ========== Active Movement ========== //
	virtual void ActiveComponent(bool bResetCount = true) override;

	virtual void DeactiveComponent() override;
	// ===================================== //


protected:
	// ========== Target Componet ========== //
	virtual void InitializeTarget();
	// ===================================== //

	
	// ========== Movement ========== //
	virtual void ResetCount();
	
	virtual void InitializePhase();

	virtual void UninitializePhase();
	
	virtual void TickMovement(float DeltaTime);
	// ============================== //

	
protected:
	// ========== Active Component ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	bool bActiveMovement_OnStart;
	
	UPROPERTY()
	bool bActiveMovement;
	// ====================================== //


	// ========== Target Componet ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	FName Tag_TargetComponet;
	
	UPROPERTY()
	TArray<TObjectPtr<USceneComponent>> TargetComponents;
	// ===================================== //

	
	// ========== Movement ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	FITTRotationData RotationData;

	UPROPERTY()
	int32 Phase;

	UPROPERTY()
	float ElapsedTimeInPhase;

	UPROPERTY()
	FRotator RotationValueForSec;
	// ============================== //


public:
	// ==================== Delegate ==================== //
	// ========== Active Component ========== //
	FITTActorComponentActiveDelegate ActorComponentActiveDelegate;

	FITTActorComponentDeactiveDelegate ActorComponentDeactiveDelegate;
	// ====================================== //
	// ================================================== //
};
