// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTGameMode_LocalMultiplay.h"

#include "Kismet/GameplayStatics.h"


AITTGameMode_LocalMultiplay::AITTGameMode_LocalMultiplay()
{
}


// ========== Player ========== //
void AITTGameMode_LocalMultiplay::AdjustPlayer()
{
	int32 CurrentPlayerNum = GetNumPlayers();
	
	ITTCHECKF(CurrentPlayerNum <= LocalPlayerNum, TEXT("[%s] Current number of players is greater than allowed"), *ITTSTRING_FUNC);
	
	for (int32 i = CurrentPlayerNum; i < LocalPlayerNum; ++i)
	{
		UGameplayStatics::CreatePlayer(this, i);
	}
}
// ============================ //