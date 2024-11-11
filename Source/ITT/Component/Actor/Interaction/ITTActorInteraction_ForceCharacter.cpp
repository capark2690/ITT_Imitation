// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTActorInteraction_ForceCharacter.h"

#include "Character/ITTCharacterBase.h"
#include "Component/Actor/Switch/ITTSwitchComponent.h"
#include "Component/Character/Movement/ITTCharacterMovementComponent.h"
#include "Component/ComponentInterface/Actor/ITTInteractableCollisionInterface.h"
#include "Components/PrimitiveComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/Actor.h"


UITTActorInteraction_ForceCharacter::UITTActorInteraction_ForceCharacter()
{
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}


void UITTActorInteraction_ForceCharacter::InitializeComponent()
{
	Super::InitializeComponent();

	RegisterBindCollisionComponents();
	BindInteractEvent();
}

void UITTActorInteraction_ForceCharacter::UninitializeComponent()
{
	Super::UninitializeComponent();
}

void UITTActorInteraction_ForceCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void UITTActorInteraction_ForceCharacter::TickComponent(float DeltaTime, ELevelTick TickType,
                                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bActiveInteraction)
	{
		ForceChangeCharacterMovementMode(ElapsedTime);
		ForceChangeCharacterLocation(ElapsedTime);
		ForceChangeCharacterMovementMode(ElapsedTime);

		CheckTriggerSwitch(ElapsedTime);

		if (ElapsedTime > MaxTime)
		{
			bActiveInteraction = false;
			return;
		}
		
		ElapsedTime += DeltaTime;
	}
}


// ========== Interact ========== //
void UITTActorInteraction_ForceCharacter::RegisterBindCollisionComponents()
{
	if (GetOwner())
	{
		for (FName& CollisionTag : BindCollisionTags)
		{
			TArray<UActorComponent*> TaggedComponents = GetOwner()->GetComponentsByTag(UPrimitiveComponent::StaticClass(), CollisionTag);
			for (UActorComponent* TaggedComponent : TaggedComponents)
			{
				if (UPrimitiveComponent* CollisionComponent = Cast<UPrimitiveComponent>(TaggedComponent))
				{
					BindCollisionComponents.AddUnique(CollisionComponent);
				}
			}
		}
	}
}

void UITTActorInteraction_ForceCharacter::BindInteractEvent()
{
	for (TWeakObjectPtr<UPrimitiveComponent> CollisionComponent : BindCollisionComponents)
	{
		if (CollisionComponent != nullptr)
		{
			if (IITTInteractableCollisionInterface* InteractableCollisionComponent = Cast<IITTInteractableCollisionInterface>(CollisionComponent.Get()))
			{
				InteractableCollisionComponent->GetInteractDelegate()->AddUObject(this, &UITTActorInteraction_ForceCharacter::OnInteract);
			}
		}
	}
}

void UITTActorInteraction_ForceCharacter::OnInteract(UPrimitiveComponent* _InteractionCollision,
	AITTCharacterBase* _InteractorCharacter)
{
	InteractionCollision = _InteractionCollision;
	InteractorCharacter = _InteractorCharacter;
	InteractorMovementComponent = Cast<UITTCharacterMovementComponent>(InteractorCharacter->GetCharacterMovement());

	bActiveInteraction = true;
	ElapsedTime = 0.f;

	MovementChangeValueIndex = -1;

	SwitchTriggerDataIndex = -1;
	
	if (bChange_Location_Static)
	{
		InteractorCharacter->SetActorLocation(StaticValues_Location);
	}

	if (bChange_Rotation_Static)
	{
		InteractorCharacter->SetActorRotation(StaticValues_Rotation);
	}
}
// ============================= //


// ========== Force Character ========== //
void UITTActorInteraction_ForceCharacter::ForceChangeCharacterMovementMode(float Time)
{
	if (ChangeValues_CharacterMovementMode.IsValidIndex(MovementChangeValueIndex + 1))
	{
		if (Time >= ChangeValues_CharacterMovementMode[MovementChangeValueIndex + 1].Time)
		{
			InteractorMovementComponent->SetITTMovementMode(ChangeValues_CharacterMovementMode[MovementChangeValueIndex + 1].MovementMode);

			MovementChangeValueIndex += 1;
		}
	}
}

void UITTActorInteraction_ForceCharacter::ForceChangeCharacterLocation(float Time)
{
	InteractorCharacter->SetActorLocation(ChangeCurve_Location->GetVectorValue(Time));
}

void UITTActorInteraction_ForceCharacter::ForceChangeCharacterRocation(float Time)
{
	InteractorCharacter->SetActorRotation(ChangeCurve_Rotation->GetVectorValue(Time).ToOrientationRotator());
}
// ===================================== //


// ========== Switch ========== //
void UITTActorInteraction_ForceCharacter::CheckTriggerSwitch(float Time)
{
	if (SwitchTriggerData.IsValidIndex(SwitchTriggerDataIndex + 1))
	{
		if (Time >= SwitchTriggerData[SwitchTriggerDataIndex + 1].Time)
		{
			TArray<UActorComponent*> TaggedComponents = GetOwner()->GetComponentsByTag(UITTSwitchComponent::StaticClass(), SwitchTriggerData[SwitchTriggerDataIndex + 1].SwitchTag);
			for (UActorComponent* TaggedComponent : TaggedComponents)
			{
				if (UITTSwitchComponent* SwitchComponent = Cast<UITTSwitchComponent>(TaggedComponent))
				{
					SwitchComponent->SetConditionSatisfaction(SwitchTriggerData[SwitchTriggerDataIndex + 1].SwitchConditionKey, SwitchTriggerData[SwitchTriggerDataIndex + 1].bSatisfy);
				}
			}
			
			SwitchTriggerDataIndex += 1;
		}
	}
}
// ============================ //