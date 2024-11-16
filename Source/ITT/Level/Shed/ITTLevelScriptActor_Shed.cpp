// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTLevelScriptActor_Shed.h"


AITTLevelScriptActor_Shed::AITTLevelScriptActor_Shed()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AITTLevelScriptActor_Shed::BeginPlay()
{
	Super::BeginPlay();
}

void AITTLevelScriptActor_Shed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Level Sequences ========== //
ALevelSequenceActor* AITTLevelScriptActor_Shed::GetLevelSequenceActor(const FName& Key) const
{
	if (LevelSequenceActors.Contains(Key))
	{
		return *LevelSequenceActors.Find(Key);
	}

	return nullptr;
}
// ===================================== //
