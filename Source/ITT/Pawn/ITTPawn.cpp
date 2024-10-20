// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTPawn.h"


AITTPawn::AITTPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AITTPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AITTPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Input ========== //
void AITTPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
// =========================== //
