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


	// ========== Actor ========== //
	void AddLevelSpecificActor(const FName& Key, class AActor* Actor);
	void RemoveLevelSpecificActor(const FName& Key);
	
	class AActor* GetLevelSpecificActor(const FName& Key) const;

	template<typename TClass>
	TClass* GetLevelSpecificActor(const FName& Key) const
	{
		return Cast<TClass>(GetLevelSpecificActor(Key));
	}
	// =========================== //

	
	// ========== Level Sequences ========== //
	class ALevelSequenceActor* GetLevelSequenceActor(const FName& Key) const;
	// ===================================== //

	
protected:
	// ========== Cameras ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	TMap<FName, TObjectPtr<AActor>> ViewTargetActors;
	// ============================= //

	
	// ========== Actors ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	TMap<FName, TObjectPtr<class AActor>> LevelSpecificActors;
	// ============================ //

	
	// ========== Level Sequences ========== //
	UPROPERTY(Category=ITT, EditAnywhere)
	TMap<FName, TObjectPtr<class ALevelSequenceActor>> LevelSequenceActors;
	// ===================================== //
};
