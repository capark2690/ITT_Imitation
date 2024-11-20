// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "ITTLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AITTLevelScriptActor();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	
	// ========== Camera ========== //
	class AActor* GetViewTargetActor(const FName& Key);
	// ============================ //

	
	// ========== Level Sequences ========== //
	class ALevelSequenceActor* GetLevelSequenceActor(const FName& Key) const;
	// ===================================== //

	
protected:
	// ========== Camera ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	TMap<FName, AActor*> ViewTargetActors;
	// ============================ //

	
	// ========== Level Sequences ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	TMap<FName, class ALevelSequenceActor*> LevelSequenceActors;
	// ===================================== //
};
