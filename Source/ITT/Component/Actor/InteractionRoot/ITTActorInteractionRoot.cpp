﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTActorInteractionRoot.h"


UITTActorInteractionRoot::UITTActorInteractionRoot()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTActorInteractionRoot::BeginPlay()
{
	Super::BeginPlay();
}

void UITTActorInteractionRoot::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

