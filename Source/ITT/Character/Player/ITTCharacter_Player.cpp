// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTCharacter_Player.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Component/Character/Input/ITTInputHelperComponent.h"
#include "Component/Character/Interaction/ITTPlayerInteractionComponent.h"
#include "Component/Character/Movement/ITTCharacterMovementComponent_Player.h"
#include "Component/Character/Stat/ITTCharacterStatComponent_Player.h"

#include "Data/DataAssets/Camera/CameraSettings/ITTData_CameraSettings_WithSpringArm.h"


AITTCharacter_Player::AITTCharacter_Player(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UITTCharacterMovementComponent_Player>(ACharacter::CharacterMovementComponentName)
		.SetDefaultSubobjectClass<UITTCharacterStatComponent_Player>(TEXT("CharacterStatComponent")))
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 100.0f);
		
	// Set use controller rotaion
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
		
	// Create input helper component
	InputHelperComponent = CreateDefaultSubobject<UITTInputHelperComponent>(TEXT("InputHelperComponent"));

	// Create player interaction component
	PlayerInteractionComponent = CreateDefaultSubobject<UITTPlayerInteractionComponent>(TEXT("PlayerInteractionComponent"));
}


void AITTCharacter_Player::BeginPlay()
{
	Super::BeginPlay();
}

void AITTCharacter_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Camera ========== //
void AITTCharacter_Player::SetCameraSettings(UITTData_CameraSettings* Data_CameraSettings)
{
	if (UITTData_CameraSettings_WithSpringArm* Data_CameraSettings_WithSpringArm = Cast<UITTData_CameraSettings_WithSpringArm>(Data_CameraSettings))
	{
		if (CameraBoom)
		{
			CameraBoom->TargetArmLength = Data_CameraSettings_WithSpringArm->SpringArm_TargetArmLength;
			CameraBoom->TargetOffset = Data_CameraSettings_WithSpringArm->SpringArm_TargetOffset;
		}

		if (FollowCamera)
		{
			FollowCamera->SetRelativeRotation(Data_CameraSettings_WithSpringArm->Camera_Rotator);
		}
	}
}
// ============================ //


// ========== Movement ========== //
// -- Jump -- //
void AITTCharacter_Player::Jump()
{
	if (!CanJump())
	{
		if (UITTCharacterMovementComponent_Player* MovementComponent_Player = Cast<UITTCharacterMovementComponent_Player>(GetMovementComponent()))
		{
			if (MovementComponent_Player->IsWallSlide() || MovementComponent_Player->IsLedgeGrab())
			{
				MovementComponent_Player->SetITTMovementMode<EITTSubMovementMode_Falling>(EMovementMode::MOVE_Falling, EITTSubMovementMode_Falling::Falling_InAir);
				
				FVector LaunchVelocity = -GetActorForwardVector() * MovementComponent_Player->LaunchVelocityMultiply;
				LaunchVelocity.Z += MovementComponent_Player->LaunchVelocityZAdditive;
				
				LaunchCharacter(LaunchVelocity, true, false);
			}
		}
	}
	else
	{
		Super::Jump();
	}
}

bool AITTCharacter_Player::CanJumpInternal_Implementation() const
{
	return Super::CanJumpInternal_Implementation();
}
// ============================== //


// ========== Input ========== //
void AITTCharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputHelperComponent->SetupPlayerInputComponent(PlayerInputComponent);
}
// =========================== //
