// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ITTWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UITTWidgetComponent();


	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	
	// ========== Overlap ========== //
	virtual void BindOverlapEvent();

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// ============================= //

	
	// ========== Overlapped Components ========== //
	void RegisterOverlappedComponent(class UPrimitiveComponent* OverlappedComponent);
	
	void UnregisterOverlappedComponent(class UPrimitiveComponent* OverlappedComponent);
	// =========================================== //

	
	// ========== State ========== //
	void UpdateCurrentState();
	// =========================== //

	
protected:
	// ========== Overlapped Components ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	TArray<FName> CollisionTags;

	UPROPERTY()
	TArray<TWeakObjectPtr<class UPrimitiveComponent>> OverlappedComponents;
	// =========================================== //


	// ========== State ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	TMap<int32, int32> CollisionPriorityToStateId;
	// =========================== //
};
