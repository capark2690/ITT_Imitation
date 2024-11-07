// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTPlayerInteractionComponent.h"

#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

#include "Component/ComponentInterface/Actor/ITTCollisionBaseInterface.h"
#include "Component/ComponentInterface/Actor/ITTInteractableCollisionInterface.h"


UITTPlayerInteractionComponent::UITTPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UITTPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ========== Interaction ========== //
void UITTPlayerInteractionComponent::InputInteraction()
{
	if (IITTInteractableCollisionInterface* TargetCollision = GetOverridedInteractionCollision())
	{
		TargetCollision->Interact();
	}
}

IITTInteractableCollisionInterface* UITTPlayerInteractionComponent::GetOverridedInteractionCollision() const
{
	IITTInteractableCollisionInterface* Ret = nullptr;
	int32 Priority = -1;
	
	TArray<UPrimitiveComponent*> OverlappingComponents;
	GetOwner()->GetOverlappingComponents(OverlappingComponents);
	
	for (UPrimitiveComponent* OverlappingComponent : OverlappingComponents)
	{
		if (IITTInteractableCollisionInterface* InteractableCollision = Cast<IITTInteractableCollisionInterface>(OverlappingComponent))
		{
			if (IITTCollisionBaseInterface* InteractableCollisionByCollisionBase = Cast<IITTCollisionBaseInterface>(InteractableCollision))
			{
				if (InteractableCollisionByCollisionBase->GetPriority() < 0)
				{
					continue;
				}
			
				if (Ret != nullptr)
				{
					if (InteractableCollisionByCollisionBase->GetPriority() <= Priority)
					{
						continue;
					}
				}

				Ret = InteractableCollision;
				Priority = InteractableCollisionByCollisionBase->GetPriority();
			}
		}
	}

	return Ret;
}
// ================================= //