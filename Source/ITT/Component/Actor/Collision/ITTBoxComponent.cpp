// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTBoxComponent.h"

#include "Component/Actor/Widget/ITTWidgetComponent.h"


UITTBoxComponent::UITTBoxComponent()
	: Priority(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTBoxComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UITTBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ========== Priority ========== //
int32 UITTBoxComponent::GetPriority()
{
	return Priority;
}
// ============================== //