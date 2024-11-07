// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSwitchComponent.h"

#include "GameFramework/Actor.h"

#include "Component/ComponentInterface/Actor/ITTSwitchTargetComponentInterface.h"


UITTSwitchComponent::UITTSwitchComponent()
	: bSwitchOnOnly(true), bSwitchOn(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UITTSwitchComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeTarget();

	if (CheckAllConditionSatisfied())
	{
		SwitchOn();
	}
}


// ========== Target Componet ========== //
void UITTSwitchComponent::InitializeTarget()
{
	if (GetOwner())
	{
		TargetComponents.Reset();
		
		TArray<UActorComponent*> TaggedComponents = GetOwner()->GetComponentsByTag(UActorComponent::StaticClass(), Tag_TargetComponet);
		for (UActorComponent* TaggedComponent : TaggedComponents)
		{
			if (IITTSwitchTargetComponentInterface* TargetComponent = Cast<IITTSwitchTargetComponentInterface>(TaggedComponent))
			{
				TargetComponents.Add(TargetComponent);
			}
			else
			{
				ITTLOG(Error, TEXT("[%s] TargetComponent does not inherit 'IITTSwitchTargetComponentInterface'."), *ITTSTRING_FUNC);
			}
		}
	}
}
// ===================================== //


// ========== Condition ========== //
void UITTSwitchComponent::SetConditionSatisfaction(const FName& ConditionKey, bool bSatisfied)
{
	if (Conditions.Contains(ConditionKey))
	{
		*Conditions.Find(ConditionKey) = bSatisfied;
	}
	else
	{
		ITTLOG(Error, TEXT("[%s] Condition Key is not valid."), *ITTSTRING_FUNC);
	}

	if (!bSwitchOn && CheckAllConditionSatisfied())
	{
		SwitchOn();
		return;
	}

	if (!bSwitchOnOnly && bSwitchOn && !CheckAllConditionSatisfied())
	{
		SwitchOff();
	}
}

bool UITTSwitchComponent::CheckAllConditionSatisfied()
{
	for (auto& Condition : Conditions)
	{
		if (Condition.Value == false)
		{
			return false;
		}
	}

	return true;
}
// =============================== //


// ========== Switch ========== //
void UITTSwitchComponent::SwitchOn()
{
	if (!bSwitchOn)
	{
		bSwitchOn = true;
	
		for (IITTSwitchTargetComponentInterface* TargetComponent : TargetComponents)
		{
			TargetComponent->ActiveComponent();
		}
	}
}

void UITTSwitchComponent::SwitchOff()
{
	if (bSwitchOn)
	{
		bSwitchOn = false;
	
		for (IITTSwitchTargetComponentInterface* TargetComponent : TargetComponents)
		{
			TargetComponent->DeactiveComponent();
		}
	}
}
// ============================ //