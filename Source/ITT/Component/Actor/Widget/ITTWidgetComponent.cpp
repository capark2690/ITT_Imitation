// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidgetComponent.h"

#include "Component/ComponentInterface/Actor/ITTCollisionBaseInterface.h"

#include "GUI/Widget/WidgetInterface/ITTWidgetComponentAttachable.h"


UITTWidgetComponent::UITTWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	BindOverlapEvent();
}

void UITTWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ========== Overlap ========== //
void UITTWidgetComponent::BindOverlapEvent()
{
	if (GetOwner())
	{
		for (FName& CollisionTag : CollisionTags)
		{
			TArray<UActorComponent*> TaggedComponents = GetOwner()->GetComponentsByTag(UPrimitiveComponent::StaticClass(), CollisionTag);
			for (UActorComponent* TaggedComponent : TaggedComponents)
			{
				if (UPrimitiveComponent* CollisionComponent = Cast<UPrimitiveComponent>(TaggedComponent))
				{
					CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UITTWidgetComponent::OnOverlapBegin);
					CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UITTWidgetComponent::OnOverlapEnd);
				}
			}
		}
	}
}

void UITTWidgetComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	RegisterOverlappedComponent(OverlappedComponent);
}

void UITTWidgetComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UnregisterOverlappedComponent(OverlappedComponent);
}
// ============================= //


// ========== Requested States ========== //
void UITTWidgetComponent::RegisterOverlappedComponent(UPrimitiveComponent* OverlappedComponent)
{
	if (IsValid(OverlappedComponent))
	{
		OverlappedComponents.AddUnique(OverlappedComponent);

		UpdateCurrentState();
	}
}

void UITTWidgetComponent::UnregisterOverlappedComponent(UPrimitiveComponent* OverlappedComponent)
{
	if (OverlappedComponents.Contains(OverlappedComponent))
	{
		OverlappedComponents.Remove(OverlappedComponent);

		UpdateCurrentState();
	}
}
// ====================================== //

	
// ========== State ========== //
void UITTWidgetComponent::UpdateCurrentState()
{
	int32 CollisionPriority = -1;
	
	for (UPrimitiveComponent* CollisionComponent : OverlappedComponents)
	{
		if (!IsValid(CollisionComponent))
		{
			continue;
		}
		
		if (IITTCollisionBaseInterface* CollisionComponentByInterface = Cast<IITTCollisionBaseInterface>(CollisionComponent))
		{
			if (CollisionComponentByInterface->GetPriority() > CollisionPriority)
			{
				CollisionPriority = CollisionComponentByInterface->GetPriority();
			}
		}
	}

	if (CollisionPriority < 0)
	{
		SetVisibility(false);

		if (IITTWidgetComponentAttachable* AttachableWidget = Cast<IITTWidgetComponentAttachable>(GetWidget()))
		{
			AttachableWidget->OnDeactiveWidgetComponent();
		}
	}
	else
	{
		SetVisibility(true);

		if (IITTWidgetComponentAttachable* AttachableWidget = Cast<IITTWidgetComponentAttachable>(GetWidget()))
		{
			int32 StateId  = 0;
			
			if (CollisionPriorityToStateId.Contains(CollisionPriority))
			{
				StateId = *CollisionPriorityToStateId.Find(CollisionPriority);
			}
			
			AttachableWidget->OnActiveWidgetComponent(StateId);
		}
	}
}
// =========================== //

