// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Component/ComponentInterface/Actor/ITTCollisionBaseInterface.h"
#include "ITTBoxComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTBoxComponent : public UBoxComponent, public IITTCollisionBaseInterface
{
	GENERATED_BODY()

public:
	UITTBoxComponent();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	// ========== Priority ========== //
	virtual int32 GetPriority() override;
	// ============================== //
	
	
protected:
	// ========== Priority ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	int32 Priority;
	// ============================== //
};
