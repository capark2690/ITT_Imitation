// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTPawn_CharacterSelect.h"


AITTPawn_CharacterSelect::AITTPawn_CharacterSelect()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AITTPawn_CharacterSelect::BeginPlay()
{
	Super::BeginPlay();
	
}

void AITTPawn_CharacterSelect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Input ========== //
void AITTPawn_CharacterSelect::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
// =========================== //
