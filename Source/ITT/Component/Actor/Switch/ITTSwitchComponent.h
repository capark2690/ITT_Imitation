// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actor/ITTDefine_Actor.h"
#include "Character/ITTDefine_Character.h"
#include "ITTSwitchComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTSwitchComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UITTSwitchComponent();


	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;


	// ========== Target Componet ========== //
	void InitializeTarget();
	// ===================================== //


	// ========== Condition ========== //
	void SetConditionSatisfaction(const FName& Key, bool bSatisfied);

	bool CheckAllConditionSatisfied();

	void CheckCondition();
	// =============================== //


	// ========== Switch ========== //
	void SwitchOn();
	void SwitchOff();
	// ============================ //

	
protected:
	// ========== Target Componet ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	FName Tag_TargetComponet;

	UPROPERTY()
	TArray<TWeakObjectPtr<class UActorComponent>> TargetComponents;
	// ===================================== //


	// ========== Condition ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	TMap<FName, FITTSwitchCondition> Conditions;

	UPROPERTY(Category=ITT, EditAnywhere)
	TMap<FName, bool> ConditionStates;
	// =============================== //


	// ========== All Switch ========== //
	UPROPERTY()
	bool bSwitchOn;
	// ================================ //
};
