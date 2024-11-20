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