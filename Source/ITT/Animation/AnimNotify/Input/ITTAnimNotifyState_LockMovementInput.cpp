// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTAnimNotifyState_LockMovementInput.h"

#include "Components/SkeletalMeshComponent.h"

#include "Character/Player/ITTCharacter_Player.h"
#include "Component/Character/Input/ITTInputHelperComponent.h"


void UITTAnimNotifyState_LockMovementInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                        float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AITTCharacter_Player* PlayerCharacter = Cast<AITTCharacter_Player>(MeshComp->GetOwner()))
	{
		if (UITTInputHelperComponent* InputHelperComponent = PlayerCharacter->GetInputHelperComponent())
		{
			InputHelperComponent->LockMovementInput();
		}
	}
}

void UITTAnimNotifyState_LockMovementInput::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UITTAnimNotifyState_LockMovementInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AITTCharacter_Player* PlayerCharacter = Cast<AITTCharacter_Player>(MeshComp->GetOwner()))
	{
		if (UITTInputHelperComponent* InputHelperComponent = PlayerCharacter->GetInputHelperComponent())
		{
			InputHelperComponent->UnlockMovementInput();
		}
	}
}
