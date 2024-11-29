// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "ITTWidget_Loading.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidget_Loading : public UITTWidget
{
	GENERATED_BODY()

public:
	UITTWidget_Loading(const FObjectInitializer& ObjectInitializer);

	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	// ========== Widget Animation ========== //
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
	
	virtual void OnStartLoading();
	virtual void OnEndLoading();
	// ====================================== //

	
protected:
	UPROPERTY(EditAnywhere)
	float MinLoadingTime;
	
	float LoadingTime;

	bool bEndLoading;
	
	// ========== Widget Animation ========== //
	UPROPERTY(Transient, Meta = (BindWidgetAnim))
	class UWidgetAnimation* WAnim_Appearance;

	UPROPERTY(Transient, Meta = (BindWidgetAnim))
	class UWidgetAnimation* WAnim_Disappearance;
	// ====================================== //
};
