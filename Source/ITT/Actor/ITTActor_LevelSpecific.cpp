// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTActor_LevelSpecific.h"

#include "Engine/Level.h"
#include "Engine/LevelScriptActor.h"
#include "Level/ITTLevelScriptActor.h"


AITTActor_LevelSpecific::AITTActor_LevelSpecific()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AITTActor_LevelSpecific::BuiltInInitialize(const FName& _ActorKey)
{
	ActorKey = _ActorKey;
}

void AITTActor_LevelSpecific::BeginPlay()
{
	Super::BeginPlay();

	AddToLevelSpecificActorMap();
	
}

void AITTActor_LevelSpecific::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveToLevelSpecificActorMap();
	
	Super::EndPlay(EndPlayReason);
}

void AITTActor_LevelSpecific::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Management ========== //
void AITTActor_LevelSpecific::AddToLevelSpecificActorMap()
{
	if (ULevel* Level = GetLevel())
	{
		if (AITTLevelScriptActor* LevelScriptActor = Cast<AITTLevelScriptActor>(Level->GetLevelScriptActor()))
		{
			LevelScriptActor->AddLevelSpecificActor(ActorKey, this);
		}
	}
}

void AITTActor_LevelSpecific::RemoveToLevelSpecificActorMap()
{
	if (ULevel* Level = GetLevel())
	{
		if (AITTLevelScriptActor* LevelScriptActor = Cast<AITTLevelScriptActor>(Level->GetLevelScriptActor()))
		{
			LevelScriptActor->RemoveLevelSpecificActor(ActorKey);
		}
	}
}
// ================================ //