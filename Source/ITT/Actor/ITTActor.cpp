// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTActor.h"


AITTActor::AITTActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AITTActor::BeginPlay()
{
	Super::BeginPlay();
}

void AITTActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}