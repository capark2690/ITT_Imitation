// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTLevelScriptActor.h"


AITTLevelScriptActor::AITTLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AITTLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AITTLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Camera ========== //
AActor* AITTLevelScriptActor::GetViewTargetActor(const FName& Key)
{
	if (ViewTargetActors.Contains(Key))
	{
		return *ViewTargetActors.Find(Key);
	}

	return nullptr;
}
// ============================ //


// ========== Actor ========== //
void AITTLevelScriptActor::AddLevelSpecificActor(const FName& Key, AActor* Actor)
{
	if (Key.IsNone())
	{
		ITTENSUREF(false, TEXT("[%s] Please Set ActorKey [ActorName : %s]"), *ITTSTRING_FUNC, *Actor->GetName());
		return;
	}
	
	if (LevelSpecificActors.Contains(Key))
	{
		ITTENSUREF(false, TEXT("[%s] LevelSpecificActor Key is already exist [Key : %s]"), *ITTSTRING_FUNC, *Key.ToString());
	}
	
	LevelSpecificActors.Emplace(Key, Actor);
}

void AITTLevelScriptActor::RemoveLevelSpecificActor(const FName& Key)
{
	if (Key.IsNone())
	{
		return;
	}
	
	if (!LevelSpecificActors.Contains(Key))
	{
		ITTLOG(Error, TEXT("[%s] LevelSpecificActor Key isn't exist [Key : %s]"), *ITTSTRING_FUNC, *Key.ToString());
	}
	
	LevelSpecificActors.Remove(Key);
}

AActor* AITTLevelScriptActor::GetLevelSpecificActor(const FName& Key) const
{
	if (LevelSpecificActors.Contains(Key))
	{
		return *LevelSpecificActors.Find(Key);
	}

	return nullptr;
}
// =========================== //


// ========== Level Sequences ========== //
ALevelSequenceActor* AITTLevelScriptActor::GetLevelSequenceActor(const FName& Key) const
{
	if (LevelSequenceActors.Contains(Key))
	{
		return *LevelSequenceActors.Find(Key);
	}

	return nullptr;
}
// ===================================== //