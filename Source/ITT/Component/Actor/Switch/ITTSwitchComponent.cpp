// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSwitchComponent.h"

#include "Character/ITTCharacterBase.h"
#include "Character/Player/ITTCharacter_Player.h"
#include "Component/Character/Movement/ITTCharacterMovementComponent.h"
#include "GameFramework/Actor.h"

#include "GameBase/BasicUtility/ITTBasicUtility.h"

#include "Component/ComponentInterface/Actor/ITTSwitchTargetComponentInterface.h"

#include "Data/DataAssets/Actor/Switch/Condition/ITTData_SwitchCondition.h"
#include "Data/DataAssets/Actor/Switch/Condition/ITTData_SwitchCondition_PlayerMovementMode.h"
#include "StateMachine/ITTStateMachine.h"


UITTSwitchComponent::UITTSwitchComponent()
	: bSwitchOn(false)
{
	PrimaryComponentTick.bCanEverTick = true;

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

void UITTSwitchComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckCondition();
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
		ConditionStates.FindOrAdd(ConditionKey) = bSatisfied;
	}
	else
	{
		ITTLOG(Error, TEXT("[%s] Condition Key is not valid."), *ITTSTRING_FUNC);
	}

	
	// Switch
	if (!bSwitchOn && CheckAllConditionSatisfied())
	{
		SwitchOn();
		return;
	}

	if (bSwitchOn && !CheckAllConditionSatisfied())
	{
		SwitchOff();
	}
}

bool UITTSwitchComponent::CheckAllConditionSatisfied()
{
	for (auto& ConditionState : ConditionStates)
	{
		if (ConditionState.Value == false)
		{
			return false;
		}
	}

	return true;
}

void UITTSwitchComponent::CheckCondition()
{
	for (auto& ConditionIter : Conditions)
	{
		const FITTSwitchCondition& Conditon = ConditionIter.Value;

		bool ConditionStateOn = ConditionStates.Contains(ConditionIter.Key) && *ConditionStates.Find(ConditionIter.Key);
		
		UITTData_SwitchCondition* TestData = ConditionStateOn ? Conditon.OffConditionData : Conditon.OnConditionData;
		
		if (TestData)
		{
			if (TestData->ConditionTriggerType == EITTSwitchConditionTriggerType::ChangeInteractorCharacterMovementMode)
			{
				if (UITTData_SwitchCondition_PlayerMovementMode* CastData = Cast<UITTData_SwitchCondition_PlayerMovementMode>(TestData))
				{
					if (AITTCharacter_Player* PlayerCharacter = UITTBasicUtility::GetPlayerCharacter(CastData->TargetPlayer))
					{
						if (UITTCharacterMovementComponent* MovementComponent = Cast<UITTCharacterMovementComponent>(PlayerCharacter->GetCharacterMovement()))
						{
							if (UITTStateMachine* MovementModeMachine = MovementComponent->GetMovementModeMachine())
							{
								FITTMovementMode CurrentMovementMode = FITTMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));
								if (CastData->MovementModes.Contains(CurrentMovementMode) == CastData->bInclude)
								{
									SetConditionSatisfaction(ConditionIter.Key, !ConditionStateOn);
								}
							}
						}
					}
				}
			}
		}
	}
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