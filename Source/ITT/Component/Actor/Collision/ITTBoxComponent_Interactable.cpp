﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTBoxComponent_Interactable.h"

#include "Component/Actor/InteractionRoot/ITTActorInteractionRoot.h"


UITTBoxComponent_Interactable::UITTBoxComponent_Interactable()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTBoxComponent_Interactable::BeginPlay()
{
	Super::BeginPlay();
}

void UITTBoxComponent_Interactable::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ========== Interact ========== //
void UITTBoxComponent_Interactable::Interact(AITTCharacterBase* InteractorCharacter)
{
	if (UITTActorInteractionRoot* Parent = Cast<UITTActorInteractionRoot>(GetAttachParent()))
	{
		Parent->Interact(InteractorCharacter);
	}
	
	OnActorComponentInteractDelegate.Broadcast(this, InteractorCharacter);
}

FITTOnActorComponentInteractDelegate* UITTBoxComponent_Interactable::GetInteractDelegate()
{
	return &OnActorComponentInteractDelegate;
}
// ============================== //
