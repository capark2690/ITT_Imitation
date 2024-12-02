// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTActor.h"
#include "ITTActor_LevelSpecific.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTActor_LevelSpecific : public AITTActor
{
	GENERATED_BODY()

public:
	AITTActor_LevelSpecific();


	virtual void BuiltInInitialize(const FName& _ActorKey);
	
protected:
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	virtual void Tick(float DeltaTime) override;


protected:
	// ========== Management ========== //
	virtual void AddToLevelSpecificActorMap();
	virtual void RemoveToLevelSpecificActorMap();
	// ================================ //


protected:
	// ========== Management ========== //
	UPROPERTY(Category=ITT, EditInstanceOnly)
	FName ActorKey;
	// ================================ //
};
