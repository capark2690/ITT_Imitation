// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ITTWidgetMarkerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTWidgetMarkerComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UITTWidgetMarkerComponent();


	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	// ========== Active ========== //
	void SetActiveMarker(bool bActive);

protected:
	void OnActiveMarker();
	void OnDeactiveMarker();
	// ============================ //


public:
	// ========== Marker Widget ========== //
	const FName& GetMarkerWidgetKey() const { return MarkerWidgetKey; }
	// =================================== //

	
	// ========== Mark Condition ========== //
	bool GetMarkOnCodyScreen() const { return MarkOnCodyScreen; }
	
	bool GetMarkOnMayScreen() const { return MarkOnMayScreen; }
	
	bool GetMarkOnFullScreen() const { return MarkOnFullScreen; }
	
	bool GetMarkOnSinematicFullScreen() const { return MarkOnSinematicFullScreen; }
	
	bool GetMarkOnScreen() const { return MarkOnScreen; }
	
	bool GetMarkOffScreen() const { return MarkOffScreen; }
	// ==================================== //


protected:
	// ========== Active ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	bool bActivateMarker;
	// ============================ //


	// ========== Marker Widget ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	FName MarkerWidgetKey;
	// =================================== //

	
	// ========== Mark Condition ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	bool MarkOnCodyScreen;

	UPROPERTY(Category=ITT, EditAnywhere)
	bool MarkOnMayScreen;

	UPROPERTY(Category=ITT, EditAnywhere)
	bool MarkOnFullScreen;

	UPROPERTY(Category=ITT, EditAnywhere)
	bool MarkOnSinematicFullScreen;

	UPROPERTY(Category=ITT, EditAnywhere)
	bool MarkOnScreen;

	UPROPERTY(Category=ITT, EditAnywhere)
	bool MarkOffScreen;
	// ==================================== //
};
