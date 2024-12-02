// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSphereComponent.h"


UITTSphereComponent::UITTSphereComponent()
	: Priority(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTSphereComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UITTSphereComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ========== Priority ========== //
int32 UITTSphereComponent::GetPriority()
{
	return Priority;
}
// ============================== //
