// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_Ch1_Sequence_PowerSwitchOn.h"

#include "LevelSequenceActor.h"
#include "Engine/Level.h"
#include "Engine/World.h"
#include "LevelSequencePlayer.h"

#include "Character/Player/ITTCharacter_Player.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameBase/BasicUtility/ITTBasicUtility.h"
#include "GameBase/GameManager/GameBase/ITTSceneManager.h"
#include "Level/Shed/ITTLevelScriptActor_Shed.h"


UITTScene_Ch1_Sequence_PowerSwitchOn::UITTScene_Ch1_Sequence_PowerSwitchOn()
{
}


void UITTScene_Ch1_Sequence_PowerSwitchOn::Initialize(EITTSceneType _SceneType)
{
	Super::Initialize(_SceneType);

	PlayLevelSequence();

	if (AITTCharacter_Player* Cody = UITTBasicUtility::GetPlayerCharacter(EITTCharacter_Player::Cody))
	{
		Cody->GetMesh()->SetVisibility(false);
	}
	if (AITTCharacter_Player* May = UITTBasicUtility::GetPlayerCharacter(EITTCharacter_Player::May))
	{
		May->GetMesh()->SetVisibility(false);
	}
}

void UITTScene_Ch1_Sequence_PowerSwitchOn::Finalize()
{
	Super::Finalize();
}

void UITTScene_Ch1_Sequence_PowerSwitchOn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void UITTScene_Ch1_Sequence_PowerSwitchOn::PlayLevelSequence()
{
	UWorld* World = UITTBasicUtility::GetITTWorld();
	if (!World)
	{
		return;
	}
	
	AITTLevelScriptActor_Shed* LevelScriptActor = Cast<AITTLevelScriptActor_Shed>(World->GetLevel(0)->GetLevelScriptActor());
	if (LevelScriptActor)
	{
		ALevelSequenceActor* LevelSequenceActor = LevelScriptActor->GetLevelSequenceActor(FName("PowerSwitchOn"));
		if (LevelSequenceActor)
		{
			LevelSequenceActor->SequencePlayer->Play();

			LevelSequenceActor->OnEndPlay.AddDynamic(this, &UITTScene_Ch1_Sequence_PowerSwitchOn::OnLevelSequenceEndPlay);
		}
	}
}

void UITTScene_Ch1_Sequence_PowerSwitchOn::OnLevelSequenceEndPlay(AActor* Actor , EEndPlayReason::Type Reason)
{
	if (SceneMgr)
	{
		SceneMgr->ChangeScene(EITTSceneType::Ch1_Start, EITTLoadingType::None, true);
	}

	if (AITTCharacter_Player* Cody = UITTBasicUtility::GetPlayerCharacter(EITTCharacter_Player::Cody))
	{
		Cody->GetMesh()->SetVisibility(true);
	}
	if (AITTCharacter_Player* May = UITTBasicUtility::GetPlayerCharacter(EITTCharacter_Player::May))
	{
		May->GetMesh()->SetVisibility(true);
	}
}
