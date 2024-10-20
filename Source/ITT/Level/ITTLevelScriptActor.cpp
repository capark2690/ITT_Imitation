// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTLevelScriptActor.h"

#include "GameBase/GameManager/GameBase/ITTSceneManager.h"
#include "Scene/ITTSceneBase.h"


AITTLevelScriptActor::AITTLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AITTLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	BeginScene();
}

void AITTLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Scene ========== //
void AITTLevelScriptActor::BeginScene()
{
	if (SceneMgr)
	{
		SceneMgr->GetCurrentScene()->BeginPlay();
	}
}
// =========================== //

