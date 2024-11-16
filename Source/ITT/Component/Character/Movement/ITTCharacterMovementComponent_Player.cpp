// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTCharacterMovementComponent_Player.h"


UITTCharacterMovementComponent_Player::UITTCharacterMovementComponent_Player()
	: LaunchVelocityZAdditive(1.f), LaunchVelocityMultiply(1.f)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTCharacterMovementComponent_Player::BeginPlay()
{
	Super::BeginPlay();
}

void UITTCharacterMovementComponent_Player::TickComponent(float DeltaTime, ELevelTick TickType,
												   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ========== Movement ========== //
// -- Move -- //
void UITTCharacterMovementComponent_Player::InputMove(FVector2d MovementVector)
{
	if (IsWallSlide() || IsLedgeGrab())
	{
		return;
	}

	Move(MovementVector);
}
// ============================== //
