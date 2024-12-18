﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSubAnimInstance_Movement.h"

#include "Character/ITTCharacterBase.h"
#include "Component/Character/Movement/ITTCharacterMovementComponent.h"
#include "Component/Character/Stat/ITTCharacterStatComponent.h"


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
	if (CharacterBase != nullptr && CharacterStatComponent != nullptr)
	{
		MinWalkSpeed = CharacterStatComponent->GetCharacterStat(EITTCharacterStat::MinWalkSpeed);
		MaxJogSpeed = CharacterStatComponent->GetCharacterStat(EITTCharacterStat::MaxJogSpeed);
	}
}

void UITTSubAnimInstance_Movement::UpdateMovementValue(float DeltaSeconds)
{
	if (CharacterBase != nullptr && CharacterMovementComponent != nullptr)
	{
		// Speed
		Velocity = CharacterMovementComponent->Velocity;
		ITTLOG(Verbose, TEXT("[%s] Velocity : %f, %f, %f"), *ITTSTRING_FUNC, Velocity.X, Velocity.Y, Velocity.Z);
		
		GroundSpeed = Velocity.Size2D();
		ITTLOG(Verbose, TEXT("[%s] GroundSpeed : %f"), *ITTSTRING_FUNC, GroundSpeed);

		GroundSpeedPerMaxJogSpeed = GroundSpeed / MaxJogSpeed;
		ITTLOG(Verbose, TEXT("[%s] GroundSpeedPerMaxJogSpeed : %f"), *ITTSTRING_FUNC, GroundSpeedPerMaxJogSpeed);

		bShouldMove = CharacterMovementComponent->GetCurrentAcceleration() != FVector::Zero() && GroundSpeed > MinWalkSpeed;
		ITTLOG(Verbose, TEXT("[%s] ShouldMove : %d"), *ITTSTRING_FUNC, bShouldMove ? 1 : 0);

		
		// Direction
		ForwardVector = CharacterBase->GetActorForwardVector();
		ITTLOG(Verbose, TEXT("[%s] ForwardVector : %f, %f, %f"), *ITTSTRING_FUNC, ForwardVector.X, ForwardVector.Y, ForwardVector.Z);

		// ToDo : Calc Camera Vector
		CameraVector = FVector::Zero();
		ITTLOG(Verbose, TEXT("[%s] CameraVector : %f, %f, %f"), *ITTSTRING_FUNC, CameraVector.X, CameraVector.Y, CameraVector.Z);
		
		// ToDo : Calc Camera Vector
		ForwardVectorFromCameraVector = FVector::Zero();
		ITTLOG(Verbose, TEXT("[%s] ForwardVectorFromCameraVector : %f, %f, %f"), *ITTSTRING_FUNC, ForwardVectorFromCameraVector.X, ForwardVectorFromCameraVector.Y, ForwardVectorFromCameraVector.Z);

		ControlRotation = CharacterBase->GetControlRotation();
		ITTLOG(Verbose, TEXT("[%s] ControlRotation : %f, %f, %f"), *ITTSTRING_FUNC, ControlRotation.Roll, ControlRotation.Pitch, ControlRotation.Yaw);
		
		ActorRotation = CharacterBase->GetActorRotation();
		ITTLOG(Verbose, TEXT("[%s] ActorRotation : %f, %f, %f"), *ITTSTRING_FUNC, ActorRotation.Roll, ActorRotation.Pitch, ActorRotation.Yaw);

		ActorYawFromControlYaw = ActorRotation.Yaw - ControlRotation.Yaw;
		
		if (ActorYawFromControlYaw > 180.f)
		{
			ActorYawFromControlYaw -= 360.f;
		}
		else if (ActorYawFromControlYaw < -180.f)
		{
			ActorYawFromControlYaw += 360.f;
		}
		
		ITTLOG(Verbose, TEXT("[%s] ActorYawFromControlYaw : %f"), *ITTSTRING_FUNC, ActorYawFromControlYaw);
		
		if (ActorYawFromControlYaw > 80.f || ActorYawFromControlYaw < -80.f)
		{
			FaceYaw_Target = 0.f;
		}
		else
		{
			FaceYaw_Target = ActorYawFromControlYaw * 0.66;
		}
		
		ITTLOG(Verbose, TEXT("[%s] FaceYaw_Target : %f"), *ITTSTRING_FUNC, FaceYaw_Target);

		FaceYaw = FaceYaw_Cached + (FaceYaw_Target - FaceYaw_Cached) * (DeltaSeconds / 0.2f);
		ITTLOG(Verbose, TEXT("[%s] FaceYaw_Cached : %f"), *ITTSTRING_FUNC, FaceYaw_Cached);
		ITTLOG(Verbose, TEXT("[%s] FaceYaw : %f"), *ITTSTRING_FUNC, FaceYaw);
		
		FaceYaw_Cached = FaceYaw;
	}
}
// ==================================== //