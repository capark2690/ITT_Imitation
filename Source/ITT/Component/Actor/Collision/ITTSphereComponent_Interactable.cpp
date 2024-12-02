// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSphereComponent_Interactable.h"

#include "Component/Actor/InteractionRoot/ITTActorInteractionRoot.h"


UITTSphereComponent_Interactable::UITTSphereComponent_Interactable()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTSphereComponent_Interactable::BeginPlay()
{
	Super::BeginPlay();
}


void UITTSphereComponent_Interactable::TickComponent(float DeltaTime, ELevelTick TickType,
                                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ========== Interact ========== //
void UITTSphereComponent_Interactable::InputInteract(AITTCharacterBase* InteractorCharacter)
{
	if (UITTActorInteractionRoot* Parent = Cast<UITTActorInteractionRoot>(GetAttachParent()))
	{
		Parent->InputInteract(InteractorCharacter, false);
	}
}
// ============================== //