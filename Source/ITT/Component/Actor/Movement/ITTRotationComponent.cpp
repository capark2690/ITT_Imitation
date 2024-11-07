// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTRotationComponent.h"

#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"


UITTRotationComponent::UITTRotationComponent()
	: bActiveMovement_OnStart(false), bActiveMovement(false), Phase(0), ElapsedTimeInPhase(0.f), RotationValueForSec(FRotator::ZeroRotator)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.bStartWithTickEnabled = false;

	bWantsInitializeComponent = true;
}


void UITTRotationComponent::InitializeComponent()
{
	Super::InitializeComponent();

	InitializeTarget();
}

void UITTRotationComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
}

void UITTRotationComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (bActiveMovement_OnStart)
	{
		ActiveComponent();
	}
}

void UITTRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bActiveMovement)
	{
		TickMovement(DeltaTime);
	}
}


// ========== Active Movement ========== //
void UITTRotationComponent::ActiveComponent(bool bResetCount)
{
	if (!bActiveMovement)
	{
		bActiveMovement = true;
		
		PrimaryComponentTick.SetTickFunctionEnable(true);
	
		if (bResetCount)
		{
			ResetCount();
		}
	
		InitializePhase();

		bool bDelegateBound = ActorComponentActiveDelegate.ExecuteIfBound();
	}
}

void UITTRotationComponent::DeactiveComponent()
{
	if (bActiveMovement)
	{
		bActiveMovement = false;
		
		PrimaryComponentTick.SetTickFunctionEnable(false);
	
		UninitializePhase();
	
		bool bDelegateBound = ActorComponentDeactiveDelegate.ExecuteIfBound();
	}
}
// ===================================== //


// ========== Target Componet ========== //
void UITTRotationComponent::InitializeTarget()
{
	if (GetOwner())
	{
		TargetComponents.Reset();
		
		TArray<UActorComponent*> TaggedComponents = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), Tag_TargetComponet);
		for (UActorComponent* TaggedComponent : TaggedComponents)
		{
			TargetComponents.Add(Cast<USceneComponent>(TaggedComponent));
		}
	}
}
// ===================================== //


// ========== Movement ========== //
void UITTRotationComponent::ResetCount()
{
	Phase = 0;
	ElapsedTimeInPhase = 0.f;
	RotationValueForSec = FRotator::ZeroRotator;
}

void UITTRotationComponent::InitializePhase()
{
	if (RotationData.RotatioPhases.IsValidIndex(Phase))
	{
		FITTRotationPhaseData& PhaseData = RotationData.RotatioPhases[Phase];
		
		RotationValueForSec = (PhaseData.RotationValue_ForCount * PhaseData.Count) * ( 1.f / PhaseData.Time_ForCount);
	}
}

void UITTRotationComponent::UninitializePhase()
{
}

void UITTRotationComponent::TickMovement(float DeltaTime)
{
	if (RotationData.RotatioPhases.IsValidIndex(Phase))
	{
		if (RotationData.RotatioPhases[Phase].PhaseTime >= 0.f)
		{
			if (ElapsedTimeInPhase >= RotationData.RotatioPhases[Phase].PhaseTime)
			{
				if (!RotationData.RotatioPhases.IsValidIndex(Phase + 1))
				{
					DeactiveComponent();
					return;
				}

				UninitializePhase();
			
				++Phase;
				ElapsedTimeInPhase = 0.f;

				InitializePhase();
			}

			ElapsedTimeInPhase += DeltaTime;
		}

		for (TWeakObjectPtr<USceneComponent> TargetComponent : TargetComponents)
		{
			if (TargetComponent != nullptr)
			{
				TargetComponent->AddRelativeRotation(RotationValueForSec * DeltaTime, true);
			}
		}
	}
}
// ============================== //
