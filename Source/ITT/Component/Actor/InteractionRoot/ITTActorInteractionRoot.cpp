// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTActorInteractionRoot.h"

#include "Character/ITTCharacterBase.h"


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


// ========== Interact ========== //
void UITTActorInteractionRoot::InputInteract(AITTCharacterBase* Interactor, bool bStop)
{
	if (bStop)
	{
		StopInteract();
	}
	else
	{
		Interact(Interactor);
	}
}

void UITTActorInteractionRoot::Interact(AITTCharacterBase* Interactor)
{
	InteractorCharacter = Interactor;
}

void UITTActorInteractionRoot::StopInteract()
{
	InteractorCharacter = nullptr;
}
// ============================== //
