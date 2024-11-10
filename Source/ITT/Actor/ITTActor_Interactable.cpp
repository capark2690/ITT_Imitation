// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTActor_Interactable.h"


AITTActor_Interactable::AITTActor_Interactable()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AITTActor_Interactable::BeginPlay()
{
	Super::BeginPlay();
}

void AITTActor_Interactable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

