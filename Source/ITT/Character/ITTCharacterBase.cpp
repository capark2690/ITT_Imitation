﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTCharacterBase.h"


AITTCharacterBase::AITTCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}


void AITTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AITTCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}