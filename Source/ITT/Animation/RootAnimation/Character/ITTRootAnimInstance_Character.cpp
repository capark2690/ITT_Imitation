// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTRootAnimInstance_Character.h"

#include "Character/ITTCharacterBase.h"
#include "Component/Character/Animation/ITTAnimationHelperComponent.h"
#include "Component/Character/Movement/ITTCharacterMovementComponent.h"
#include "StateMachine/ITTStateMachine.h"


UITTRootAnimInstance_Character::UITTRootAnimInstance_Character()
{
}


void UITTRootAnimInstance_Character::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	InitializeOwner();
}

void UITTRootAnimInstance_Character::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateCharacterMovementMode();
}

void UITTRootAnimInstance_Character::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UITTRootAnimInstance_Character::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UITTRootAnimInstance_Character::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UITTRootAnimInstance_Character::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	InitializeOwnerComponent();
}


void UITTRootAnimInstance_Character::InitializeOwner()
{
	CharacterBase = Cast<AITTCharacterBase>(GetOwningActor());
}

void UITTRootAnimInstance_Character::InitializeOwnerComponent()
{
	if (CharacterBase != nullptr)
	{
		AnimationHelperComponent = CharacterBase->GetAnimationHelperComponent();
		
		CharacterMovementComponent = Cast<UITTCharacterMovementComponent>(CharacterBase->GetCharacterMovement());

		if (CharacterMovementComponent != nullptr)
		{
			MovementModeMachine = CharacterMovementComponent->GetMovementModeMachine();
		}
	}
}


// ========== Movement Mode ========== //
void UITTRootAnimInstance_Character::UpdateCharacterMovementMode()
{
	if (CharacterBase != nullptr && CharacterMovementComponent != nullptr && MovementModeMachine != nullptr)
	{
		FITTMovementMode MovementMode_Temp = CurrentMovementMode;
		
		CurrentMovementMode.SetUsingFullMode(MovementModeMachine->GetCurrentStateId());

		if (MovementMode_Temp != CurrentMovementMode)
		{
			UpdateSubAnimation();
		}
	}
}
// =================================== //


// ========== SubAnimation ========== //
void UITTRootAnimInstance_Character::UpdateSubAnimation()
{
	if (TSubclassOf<UAnimInstance> SubAnimInstanceClass = GetSubAnimInstanceClass(CurrentMovementMode))
	{
		LinkAnimClassLayers(SubAnimInstanceClass);
	}
}

TSubclassOf<UAnimInstance> UITTRootAnimInstance_Character::GetSubAnimInstanceClass(
	const FITTMovementMode& MovementMode) const
{
	if (CharacterBase != nullptr && AnimationHelperComponent != nullptr)
	{
		return AnimationHelperComponent->GetSubAnimInstanceClass(MovementMode);
	}

	return nullptr;
}
// ================================== //