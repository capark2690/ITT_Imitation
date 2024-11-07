// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSwitchComponent.h"

#include "GameFramework/Actor.h"

#include "Component/ComponentInterface/Actor/ITTSwitchTargetComponentInterface.h"


UITTSwitchComponent::UITTSwitchComponent()
	: bSwitchOnOnly(true), bSwitchOn(false)
{
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}


void UITTSwitchComponent::InitializeComponent()
{
	Super::InitializeComponent();

	InitializeTarget();
}

void UITTSwitchComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
}

void UITTSwitchComponent::BeginPlay()
{
	Super::BeginPlay();
	
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
			if (IITTSwitchTargetComponentInterface* SwitchTargetComponent = Cast<IITTSwitchTargetComponentInterface>(TaggedComponent))
			{
				TargetComponents.Add(TaggedComponent);
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
	
		for (TWeakObjectPtr<UActorComponent> TargetComponent : TargetComponents)
		{
			if (IITTSwitchTargetComponentInterface* SwitchTargetComponent = Cast<IITTSwitchTargetComponentInterface>(TargetComponent.Get()))
			{
				SwitchTargetComponent->ActiveComponent();
			}
		}
	}
}

void UITTSwitchComponent::SwitchOff()
{
	if (bSwitchOn)
	{
		bSwitchOn = false;

		for (TWeakObjectPtr<UActorComponent> TargetComponent : TargetComponents)
		{
			if (IITTSwitchTargetComponentInterface* SwitchTargetComponent = Cast<IITTSwitchTargetComponentInterface>(TargetComponent.Get()))
			{
				SwitchTargetComponent->DeactiveComponent();
			}
		}
	}
}
// ============================ //