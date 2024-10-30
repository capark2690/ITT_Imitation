// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTGameMode_Title.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


AITTGameMode_Title::AITTGameMode_Title()
{
}


void AITTGameMode_Title::BeginPlay()
{
	Super::BeginPlay();
	
	AdjustPlayer();
}


// ========== Player ========== //
void AITTGameMode_Title::AdjustPlayer()
{
	int32 CurrentPlayerNum = GetNumPlayers();
	
	ITTCHECKF(CurrentPlayerNum <= LocalPlayerNum, TEXT("[%s] Current number of players is greater than allowed"), *ITTSTRING_FUNC);
	
	for (int32 i = CurrentPlayerNum; i < LocalPlayerNum; ++i)
	{
		UGameplayStatics::CreatePlayer(this, i);
	}
}
// ============================ //