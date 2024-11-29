// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidgetMarkerComponent.h"

#include "GameBase/GameManager/Object/ITTActorManager.h"


UITTWidgetMarkerComponent::UITTWidgetMarkerComponent()
	: bActivateMarker(true), MarkOnCodyScreen(true), MarkOnMayScreen(true)
	, MarkOnFullScreen(true), MarkOnSinematicFullScreen(false), MarkOnScreen(true), MarkOffScreen(true)
{
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}


void UITTWidgetMarkerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (bActivateMarker)
	{
		OnActiveMarker();
	}
}

void UITTWidgetMarkerComponent::UninitializeComponent()
{
	OnDeactiveMarker();
	
	Super::UninitializeComponent();
}

void UITTWidgetMarkerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UITTWidgetMarkerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ========== Active ========== //
void UITTWidgetMarkerComponent::SetActiveMarker(bool bActive)
{
	if (bActivateMarker != bActive)
	{
		bActivateMarker = bActive;

		if (bActivateMarker)
		{
			OnActiveMarker();
		}
		else
		{
			OnDeactiveMarker();
		}
	}
}

void UITTWidgetMarkerComponent::OnActiveMarker()
{
	if (ActorMgr)
	{
		ActorMgr->RegisterMarkerComponent(this);
	}
}

void UITTWidgetMarkerComponent::OnDeactiveMarker()
{
	if (ActorMgr)
	{
		ActorMgr->UnregisterMarkerComponent(this);
	}
}
// ============================ //
