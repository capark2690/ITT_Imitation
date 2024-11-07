// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTInputHelperComponent.h"

#include "Engine/LocalPlayer.h"
#include "GameFramework/Controller.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

#include "Character/Player/ITTCharacter_Player.h"
#include "Component/Character/Movement/ITTCharacterMovementComponent_Player.h"
#include "Component/Character/Interaction/ITTPlayerInteractionComponent.h"


UITTInputHelperComponent::UITTInputHelperComponent()
	: bLockMovementInput(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTInputHelperComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UITTInputHelperComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// ========== Input ========== //
void UITTInputHelperComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Character = Cast<AITTCharacter_Player>(GetOwner());

	CharacterMovementComponent = Cast<UITTCharacterMovementComponent_Player>(Character->GetMovementComponent());
	PlayerInteractionComponent = Cast<UITTPlayerInteractionComponent>(Character->GetPlayerInteractionComponent());
	
	// Add Input Mapping Context
	if (Character.IsValid())
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(MappingContext, 1);
			}
		}

		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			// Movement
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UITTInputHelperComponent::InputMove);
		
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputJump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &UITTInputHelperComponent::InputStopJumping);
		
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UITTInputHelperComponent::InputLook);

			EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputDash);

			EnhancedInputComponent->BindAction(GroundPound_Crouch_Action, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputGroundPound_Crouch);
			EnhancedInputComponent->BindAction(GroundPound_Crouch_Action, ETriggerEvent::Completed, this, &UITTInputHelperComponent::InputStopGroundPound_Crouch);

			EnhancedInputComponent->BindAction(Swing_GrindGrapple_Action, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputSwing_GrindGrapple);
			EnhancedInputComponent->BindAction(Swing_GrindGrapple_Action, ETriggerEvent::Completed, this, &UITTInputHelperComponent::InputStopSwing_GrindGrapple);

			EnhancedInputComponent->BindAction(ToggleSprintAction, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputToggleSprint);
			EnhancedInputComponent->BindAction(ToggleSprintAction, ETriggerEvent::Completed, this, &UITTInputHelperComponent::InputStopToggleSprint);

			// Ability
			EnhancedInputComponent->BindAction(Ability1_Fire_Action, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputAbility1_Fire);
			EnhancedInputComponent->BindAction(Ability1_Fire_Action, ETriggerEvent::Completed, this, &UITTInputHelperComponent::InputStopAbility1_Fire);

			EnhancedInputComponent->BindAction(Ability2_Aim_Action, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputAbility2_Aim);
			EnhancedInputComponent->BindAction(Ability2_Aim_Action, ETriggerEvent::Completed, this, &UITTInputHelperComponent::InputStopAbility2_Aim);

			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputInteract);

			EnhancedInputComponent->BindAction(CancelAction, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputCancel);
		
			EnhancedInputComponent->BindAction(FindOtherPlayerAction, ETriggerEvent::Started, this, &UITTInputHelperComponent::InputFindOtherPlayer);
		}
	}
}


// -- Movement -- //
void UITTInputHelperComponent::InputMove(const FInputActionValue& Value)
{
	if (!bLockMovementInput)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();

		if (CharacterMovementComponent != nullptr)
		{
			CharacterMovementComponent->InputMove(MovementVector);
		}
	}
}

void UITTInputHelperComponent::InputJump(const FInputActionValue& Value)
{
	if (!bLockMovementInput)
	{
		Character->Jump();
	}
}

void UITTInputHelperComponent::InputStopJumping(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	Character->AddControllerYawInput(LookAxisVector.X);
	Character->AddControllerPitchInput(LookAxisVector.Y);
}

void UITTInputHelperComponent::InputLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	Character->AddControllerYawInput(LookAxisVector.X);
	Character->AddControllerPitchInput(LookAxisVector.Y);
}

void UITTInputHelperComponent::InputDash(const FInputActionValue& Value)
{
	if (!bLockMovementInput)
	{
		if (Character != nullptr && CharacterMovementComponent != nullptr)
		{
			CharacterMovementComponent->Dash();
		}
	}
}

void UITTInputHelperComponent::InputGroundPound_Crouch(const FInputActionValue& Value)
{
}

void UITTInputHelperComponent::InputStopGroundPound_Crouch(const FInputActionValue& Value)
{
}

void UITTInputHelperComponent::InputSwing_GrindGrapple(const FInputActionValue& Value)
{
}

void UITTInputHelperComponent::InputStopSwing_GrindGrapple(const FInputActionValue& Value)
{
}

void UITTInputHelperComponent::InputToggleSprint(const FInputActionValue& Value)
{
	if (!bLockMovementInput)
	{
		if (Character != nullptr && CharacterMovementComponent != nullptr)
		{
			CharacterMovementComponent->StartSprint();
		}
	}
}

void UITTInputHelperComponent::InputStopToggleSprint(const FInputActionValue& Value)
{
	if (Character != nullptr && CharacterMovementComponent != nullptr)
	{
		CharacterMovementComponent->StopSprint();
	}
}


// -- Ability -- //
void UITTInputHelperComponent::InputAbility1_Fire(const FInputActionValue& Value)
{
}

void UITTInputHelperComponent::InputStopAbility1_Fire(const FInputActionValue& Value)
{
}

void UITTInputHelperComponent::InputAbility2_Aim(const FInputActionValue& Value)
{
}

void UITTInputHelperComponent::InputStopAbility2_Aim(const FInputActionValue& Value)
{
}

void UITTInputHelperComponent::InputInteract(const FInputActionValue& Value)
{
	if (!bLockMovementInput)
	{
		if (Character != nullptr && PlayerInteractionComponent != nullptr)
		{
			PlayerInteractionComponent->InputInteraction();
		}
	}
}

void UITTInputHelperComponent::InputCancel(const FInputActionValue& Value)
{
}

void UITTInputHelperComponent::InputFindOtherPlayer(const FInputActionValue& Value)
{
}
// =========================== //


// ========== Input Control ========== //
void UITTInputHelperComponent::LockMovementInput()
{
	bLockMovementInput = true;

	InputStopJumping(FInputActionValue());
	InputStopToggleSprint(FInputActionValue());
}

void UITTInputHelperComponent::UnlockMovementInput()
{
	bLockMovementInput = false;
}
// =================================== //
