// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "ITTWidget_ActorMarker.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidget_ActorMarker : public UITTWidget
{
	GENERATED_BODY()

public:
	UITTWidget_ActorMarker(const FObjectInitializer& ObjectInitializer);
	

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
	TWeakObjectPtr<class UITTWidgetMarkerComponent> GetTargetWidgetMarkerComponent() const { return TargetWidgetMarkerComponent; }


	// ========== UMG ========== //
	void SetImageRotation(float Angle);
	// ========================= //

	
protected:
	TWeakObjectPtr<class UITTWidgetMarkerComponent> TargetWidgetMarkerComponent;

	
	UPROPERTY(EditAnywhere)
	bool bRotation;

	UPROPERTY(EditAnywhere)
	float DefaultRotationAngle;

	
	// ========== UMG ========== //
	UPROPERTY(Meta = (BindWidget))
	class UImage* IMG_Marker;
	// ========================= //
};
