// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "ITTWidget_HUD_ActorMarker.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidget_HUD_ActorMarker : public UITTWidget
{
	GENERATED_BODY()

public:
	static FName GetClassWidgetKey() { return FName(ClassWidgetKey); }

	
	UITTWidget_HUD_ActorMarker(const FObjectInitializer& ObjectInitializer);
	

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


protected:
	void BindToActorManager();
	void UnbindToActorManager();
	
	void UpdateMakerList();
	
	void UpdateMakerLocations();
	bool GetTargetScreenLocation(const FVector& InWorldLocation, FVector& OutScreenLocation, FSceneViewProjectionData& ProjectionData);

	bool IsOwnerPlayerTypeMakerable(TWeakObjectPtr<class UITTWidgetMarkerComponent> WidgetMarkerComponent) const;
	
protected:
	static constexpr char ClassWidgetKey[] = "WBP_HUD_ActorMarker";

	
	UPROPERTY()
	TMap<TObjectPtr<class UITTWidget_ActorMarker>, TWeakObjectPtr<class UITTWidgetMarkerComponent>> MarkerWidgetToMarkerComponents;
};
