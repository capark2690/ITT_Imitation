// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTCameraManager.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "GameBase/BasicUtility/ITTBasicUtility.h"


UITTCameraManager::UITTCameraManager()
{
}


// ========== Split screen ========== //
void UITTCameraManager::SetForceDisableSplitscreen(bool bDisable)
{
	if (UWorld* World = UITTBasicUtility::GetITTWorld())
	{
		if (UObject* WorldContext = World->GetFirstPlayerController())
		{
			UGameplayStatics::SetForceDisableSplitscreen(WorldContext, bDisable);
		}
	}
}
// ================================== //