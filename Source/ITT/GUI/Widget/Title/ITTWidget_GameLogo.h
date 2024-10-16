﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widget/ITTWidget.h"
#include "ITTWidget_GameLogo.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidget_GameLogo : public UITTWidget
{
	GENERATED_BODY()

	
public:
	static FName GetClassWidgetKey() { return FName(ClassWidgetKey); }

	
	UITTWidget_GameLogo(const FObjectInitializer& ObjectInitializer);
	
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	// ========== Widget Animation ========== //
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	void StartLogoAnimation();
	// ====================================== //

	
	// ========== Finish ========== //
	void ChangeScene();
	// ============================ //
	
	
protected:
	static constexpr char ClassWidgetKey[] = "WBP_GameLogo";

	
	// ========== Widget Animation ========== //
	bool bWAnimFinished;
	
	UPROPERTY(Transient, Meta = (BindWidgetAnim))
	class UWidgetAnimation* WAnim_Appearance;

	UPROPERTY(Transient, Meta = (BindWidgetAnim))
	class UWidgetAnimation* WAnim_Disappearance;
	// ====================================== //
};