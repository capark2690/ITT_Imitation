// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTActorManager.h"


UITTActorManager::UITTActorManager()
	: bBuiltInInitialized(false)
{
}

void UITTActorManager::BuiltInInitialize()
{
	bBuiltInInitialized = true;
}

void UITTActorManager::Finalize()
{
}


// ========== Marker Component ========== //
void UITTActorManager::RegisterMarkerComponent(TWeakObjectPtr<UITTWidgetMarkerComponent> MarkerComponent)
{
	MarkerComponents.AddUnique(MarkerComponent);

	bool bDelegateBound = OnUpdateActorMarker.ExecuteIfBound();
}

void UITTActorManager::UnregisterMarkerComponent(TWeakObjectPtr<UITTWidgetMarkerComponent> MarkerComponent)
{
	if (MarkerComponents.Contains(MarkerComponent))
	{
		MarkerComponents.RemoveSingle(MarkerComponent);

		bool bDelegateBound = OnUpdateActorMarker.ExecuteIfBound();
	}
}
// ====================================== //