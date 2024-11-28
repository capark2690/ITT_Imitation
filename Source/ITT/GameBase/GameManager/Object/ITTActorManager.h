// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameBase/GameManager/ITTSingleton.h"
#include "ITTActorManager.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FITTOnUpdateActorMarker);

UCLASS()
class ITT_API UITTActorManager : public UObject, public TITTSingleton<UITTActorManager>
{
	GENERATED_BODY()

public:
	UITTActorManager();
	

	virtual void BuiltInInitialize() override;
	virtual void Finalize() override;


	// ========== Marker Component ========== //
	void RegisterMarkerComponent(TWeakObjectPtr<class UITTWidgetMarkerComponent> MarkerComponent);
	void UnregisterMarkerComponent(TWeakObjectPtr<class UITTWidgetMarkerComponent> MarkerComponent);

	const TArray<TWeakObjectPtr<class UITTWidgetMarkerComponent>>& GetMarkerComponents() const { return MarkerComponents; }
	// ====================================== //
	

private:
	bool bBuiltInInitialized;


	// ========== Marker Component ========== //
	TArray<TWeakObjectPtr<class UITTWidgetMarkerComponent>> MarkerComponents;
	// ====================================== //
	

public:
	// ==================== Delegate ==================== //
	// ========== Update ========== //
	FITTOnUpdateActorMarker OnUpdateActorMarker;
	// ============================ //
	// ================================================== //

	
#define ActorMgr UITTActorManager::GetInstance()
};
