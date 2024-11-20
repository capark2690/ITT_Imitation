// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTPlayerController_LocalMultiplay.h"

#include "Engine/LocalPlayer.h"
#include "GameBase/GameManager/GameBase/ITTGameProcessManager.h"


AITTPlayerController_LocalMultiplay::AITTPlayerController_LocalMultiplay(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void AITTPlayerController_LocalMultiplay::PreInitialize(ULocalPlayer* LocalPlayer)
{
	Super::PreInitialize(LocalPlayer);

	if (GameProcessMgr)
	{
		PlayerCharacterType = GameProcessMgr->GetControllerCharacterType(LocalPlayer->GetPlatformUserId().GetInternalId());
	}

	if (PlayerCharacterType == EITTPlayerCharacterType::None)
	{
		if (LocalPlayer->GetPlatformUserId().GetInternalId() == 0)
		{
			PlayerCharacterType = EITTPlayerCharacterType::Cody;
		}
		else
		{
			PlayerCharacterType = EITTPlayerCharacterType::May;
		}
	}
}