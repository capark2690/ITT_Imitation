// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_FullScreenSequence.h"

#include "Engine/World.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

#include "GameBase/BasicUtility/ITTBasicUtility.h"
#include "GameBase/GameManager/GameBase/ITTSceneManager.h"
#include "Data/Table/Tables/GameBase/ITTTable_Scene.h"

#include "Level/ITTLevelScriptActor.h"

#include "Character/Player/ITTCharacter_Player.h"
#include "Components/SkeletalMeshComponent.h"


UITTScene_FullScreenSequence::UITTScene_FullScreenSequence()
	: SequenceName(FName())
{
}


void UITTScene_FullScreenSequence::Initialize(EITTSceneType _SceneType, FITTTableRow_Scene* _SceneRow)
{
	Super::Initialize(_SceneType, _SceneRow);

	PlayLevelSequence();

	if (AITTCharacter_Player* Cody = UITTBasicUtility::GetPlayerCharacter(EITTPlayerCharacterType::Cody))
	{
		Cody->GetMesh()->SetVisibility(false);
	}
	if (AITTCharacter_Player* May = UITTBasicUtility::GetPlayerCharacter(EITTPlayerCharacterType::May))
	{
		May->GetMesh()->SetVisibility(false);
	}
}

void UITTScene_FullScreenSequence::Finalize()
{
	Super::Finalize();
}

void UITTScene_FullScreenSequence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void UITTScene_FullScreenSequence::PlayLevelSequence()
{
	UWorld* World = UITTBasicUtility::GetITTWorld();
	if (!World)
	{
		return;
	}
	
	if (LevelScriptActor)
	{
		ITTCHECK(!SequenceName.IsNone());
		
		ALevelSequenceActor* LevelSequenceActor = LevelScriptActor->GetLevelSequenceActor(SequenceName);
		if (LevelSequenceActor)
		{
			LevelSequenceActor->GetSequencePlayer()->Play();
			
			LevelSequenceActor->GetSequencePlayer()->OnStop.AddDynamic(this, &UITTScene_FullScreenSequence::OnStopLevelSequence);
		}
	}
}

void UITTScene_FullScreenSequence::OnStopLevelSequence()
{
	if (SceneMgr)
	{
		SceneMgr->ChangeScene(SceneRow->DefaultNextSceneType, EITTLoadingType::None, true);
	}

	if (AITTCharacter_Player* Cody = UITTBasicUtility::GetPlayerCharacter(EITTPlayerCharacterType::Cody))
	{
		Cody->GetMesh()->SetVisibility(true);
	}
	if (AITTCharacter_Player* May = UITTBasicUtility::GetPlayerCharacter(EITTPlayerCharacterType::May))
	{
		May->GetMesh()->SetVisibility(true);
	}
}
