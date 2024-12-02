// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTActorInteractionRoot_FuseCrab.h"

#include "Character/ITTCharacterBase.h"
#include "Component/Character/Movement/ITTCharacterMovementComponent_Player.h"


UITTActorInteractionRoot_FuseCrab::UITTActorInteractionRoot_FuseCrab()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTActorInteractionRoot_FuseCrab::BeginPlay()
{
	Super::BeginPlay();
}

void UITTActorInteractionRoot_FuseCrab::TickComponent(float DeltaTime, ELevelTick TickType,
                                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UITTActorInteractionRoot_FuseCrab::Interact(AITTCharacterBase* Interactor)
{
	Super::Interact(Interactor);

	if (UITTCharacterMovementComponent_Player* MovementComponent = Cast<UITTCharacterMovementComponent_Player>(Interactor->GetMovementComponent()))
	{
		MovementComponent->PickUp(GetOwner());
	}
}

void UITTActorInteractionRoot_FuseCrab::StopInteract()
{
	Super::StopInteract();
}

