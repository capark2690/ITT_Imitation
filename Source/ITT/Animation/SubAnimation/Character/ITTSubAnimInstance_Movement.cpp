// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSubAnimInstance_Movement.h"


UITTSubAnimInstance_Movement::UITTSubAnimInstance_Movement()
{
}


void UITTSubAnimInstance_Movement::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	InitializeMovementValue();
}

void UITTSubAnimInstance_Movement::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	UpdateMovementValue(DeltaSeconds);
}

void UITTSubAnimInstance_Movement::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UITTSubAnimInstance_Movement::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UITTSubAnimInstance_Movement::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UITTSubAnimInstance_Movement::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}


// ========== Movement Value ========== //
void UITTSubAnimInstance_Movement::InitializeMovementValue()
{
}

void UITTSubAnimInstance_Movement::UpdateMovementValue(float DeltaSeconds)
{
}
// ==================================== //