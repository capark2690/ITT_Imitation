// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ITTWidget.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UITTWidget(const FObjectInitializer& ObjectInitializer);

	
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void BuiltInInitialize(int32 _ZOrder);


	// ========== View ========== //
	virtual void ChangeActivation(bool _bActivate);
	
protected:
	virtual void Activate_Internal();
	virtual void Deactive_Internal();
	// ========================== //
	
	
public:
	// ========== Close ========== //
	virtual void ITTCloseWidget(bool bImmediately = false);

protected:
	virtual void PrepareToFinish();
	virtual void PrepareToFinish_Immediately();
	
	UFUNCTION()
	virtual void Finish();
	// =========================== //

	
public:
	// ========== View ========== //
	bool IsActive() const { return bActive; }
	bool IsAddToViewport() const { return bAddToViewport; }
	// ========================== //

	
protected:
	// ========== View ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	bool bFullScreenWidget;
	
	bool bActive;
	bool bAddToViewport;
	
	UPROPERTY(Category=ITT, EditAnywhere)
	ESlateVisibility VisibilityOnActivate;

	int32 ZOrder;
	// ========================== //
	
	
public:
	// ==================== Delegate ==================== //
	// ========== Finish ========== //
	FITTOnReadyToFinishDelegate OnReadyToFinishDelegate;
	// ============================ //
	// ================================================== //
};