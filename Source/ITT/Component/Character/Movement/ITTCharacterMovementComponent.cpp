// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTCharacterMovementComponent.h"

#include "DrawDebugHelpers.h"
#include "ITTUtilityFunctionLibrary.h"
#include "Character/ITTCharacterFunctionLibrary.h"

#include "Character/ITTCharacterBase.h"
#include "Component/Character/Stat/ITTCharacterStatComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysicsEngine/PhysicsAsset.h"

#include "StateMachine/ITTStateMachine.h"


UITTCharacterMovementComponent::UITTCharacterMovementComponent()
	: bUseZVelotityOnlyOnWallSlide(true), ZVelocityMultiplyOnWallSlide(0.7f)
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
	
	// Configure character movement
	bOrientRotationToMovement = true;
	RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}


void UITTCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	CreateMovementModeMachine();
}

void UITTCharacterMovementComponent::UninitializeComponent()
{
	DestroyMovementModeMachine();
	
	Super::UninitializeComponent();
}

void UITTCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeBodyInstance();
	
	InitializeMovementValue();
}

void UITTCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsFalling())
	{
		OnFalling();
	}
}


// ========== Movement Mode Machine ========== //
void UITTCharacterMovementComponent::CreateMovementModeMachine()
{
	if (MovementModeMachine)
	{
		return;
	}
	
	MovementModeMachine = ITTNewObject<UITTStateMachine>(UITTStateMachine::StaticClass());
	MovementModeMachine->AddToRoot();

	// Bind OnChange delegate
	MovementModeMachine->OnChangeStateDelegate = FITTOnChangeStateDelegate::CreateUObject(this, &UITTCharacterMovementComponent::OnChangeMovementMode);
}

void UITTCharacterMovementComponent::DestroyMovementModeMachine()
{
	if (IsValid(MovementModeMachine))
	{
		MovementModeMachine->RemoveFromRoot();
		ITTDeleteObject(MovementModeMachine);
	}
}

void UITTCharacterMovementComponent::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
	if (MovementModeMachine)
	{
		uint8 MainMode = static_cast<uint8>(NewMovementMode);
		uint8 SubMode = NewCustomMode;
		
		if (UITTCharacterFunctionLibrary::CheckMovementModeValid(FITTMovementMode(MainMode, SubMode)))
		{
			int64 CurrentMovementModeValue = MovementModeMachine->GetCurrentStateId();

			if (CurrentMovementModeValue >= 0)
			{
				FITTMovementMode CurrentMovementMode(static_cast<uint32>(CurrentMovementModeValue));
		
				if (CurrentMovementMode.MainMode != MainMode)
				{
					MovementModeMachine->SetNextState
					(FITTMovementMode(MainMode, SubMode, CurrentMovementMode.AdditiveMode1, CurrentMovementMode.AdditiveMode2).GetFullMode());

					ITTLOG(Warning, TEXT("[%s] Set Movement Mode [Main : %d, Sub: %d, Additive1 : %d, Additive2 : %d"), *ITTSTRING_FUNC,
						MainMode, SubMode, 0, 0);
				}
			}
			else
			{
				MovementModeMachine->SetNextState(FITTMovementMode(MainMode, SubMode, 1, 1).GetFullMode());
			}
		}
	}
	
	Super::SetMovementMode(NewMovementMode, NewCustomMode);
}

void UITTCharacterMovementComponent::SetITTMovementMode(FITTMovementMode ITTMovementMode, bool bChangeImmediately)
{
	if (MovementModeMachine)
	{
		if (UITTCharacterFunctionLibrary::CheckMovementModeValid(ITTMovementMode))
		{
			FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

			if (ITTMovementMode.AdditiveMode1 == static_cast<uint8>(EITTAdditiveMovementMode1::PreviousValue))
			{
				ITTMovementMode.AdditiveMode1 = CurrentMovementMode.AdditiveMode1;
			}

			if (ITTMovementMode.AdditiveMode2 == static_cast<uint8>(EITTAdditiveMovementMode2::PreviousValue))
			{
				ITTMovementMode.AdditiveMode2 = CurrentMovementMode.AdditiveMode2;
			}
			
			MovementModeMachine->SetNextState(ITTMovementMode.GetFullMode(), bChangeImmediately);
			
			ITTLOG(Warning, TEXT("[%s] Set Movement Mode [Main : %d, Sub: %d, Additive1 : %d, Additive2 : %d"), *ITTSTRING_FUNC,
				ITTMovementMode.MainMode, ITTMovementMode.SubMode, ITTMovementMode.AdditiveMode1, ITTMovementMode.AdditiveMode2);
			
			if (CurrentMovementMode.MainMode != ITTMovementMode.MainMode)
			{
				Super::SetMovementMode(static_cast<EMovementMode>(ITTMovementMode.MainMode), ITTMovementMode.SubMode);
			}
		}
	}
}

void UITTCharacterMovementComponent::SetITTMovementMode(uint8 MainMode, uint8 SubMode,
	uint8 AdditiveMode1, uint8 AdditiveMode2, bool bChangeImmediately)
{
	if (MovementModeMachine)
	{
		SetITTMovementMode(FITTMovementMode(MainMode, SubMode, AdditiveMode1, AdditiveMode2), bChangeImmediately);
	}
}


// -- OnChange -- //
void UITTCharacterMovementComponent::OnChangeMovementMode(int64 PreviousMovementModeId, int64 CurrentMovementModeId)
{
	int32 DataIndex = -1;
	
	FITTMovementMode PreviousMovementMode(static_cast<uint32>(PreviousMovementModeId));
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(CurrentMovementModeId));

	// Previous Movement Mode
	if (IsSprintMode(PreviousMovementMode, DataIndex))
	{
		OnStopSprint(DataIndex);
	}

	else if (IsWallSlideMode(PreviousMovementMode))
	{
		OnStopWallSlide();
	}

	else if (IsLedgeGrabMode(PreviousMovementMode))
	{
		OnStopLedgeGrab();
	}

	if (IsPickUpMode(PreviousMovementMode) && !IsPickUpMode(CurrentMovementMode))
	{
		OnStopPickUp();
	}
	
	// Current Movement Mode
	if (IsSprintMode(CurrentMovementMode, DataIndex))
	{
		OnStartSprint(DataIndex);
	}

	else if (IsWallSlideMode(CurrentMovementMode))
	{
		OnStartWallSlide();
	}

	else if (IsLedgeGrabMode(CurrentMovementMode))
	{
		OnStartLedgeGrab();
	}

	if (!IsPickUpMode(PreviousMovementMode) && IsPickUpMode(CurrentMovementMode))
	{
		OnStartPickUp();
	}
}
// =========================================== //


// ========== Body ========== //
// -- Init -- //
void UITTCharacterMovementComponent::InitializeBodyInstance()
{
	if (AITTCharacterBase* CharacterBase = Cast<AITTCharacterBase>(GetOwner()))
	{
		LeftHandThumb = CharacterBase->GetMesh()->GetBodyInstance("LeftHandThumb1");
		RightHandThumb = CharacterBase->GetMesh()->GetBodyInstance("RightHandThumb1");
	}
}
// ========================== //


// ========== Movement ========== //
// -- Init -- //
void UITTCharacterMovementComponent::InitializeMovementValue()
{
	if (AITTCharacterBase* CharacterBase = Cast<AITTCharacterBase>(GetOwner()))
	{
		if (UITTCharacterStatComponent* CharacterStatComponent = CharacterBase->GetCharacterStatComponent())
		{
			Mass = CharacterStatComponent->GetCharacterStat(EITTCharacterStat::Mass);
			
			MaxWalkSpeed = CharacterStatComponent->GetCharacterStat(EITTCharacterStat::MaxJogSpeed);

			CharacterBase->JumpMaxCount = CharacterStatComponent->GetCharacterStat(EITTCharacterStat::JumpMaxCount);
			
			JumpZVelocity = CharacterStatComponent->GetCharacterStat(EITTCharacterStat::JumpZVelocity);
		}
	}
}


// -- Move -- //
void UITTCharacterMovementComponent::Move(FVector2d MovementVector)
{
	if (AITTCharacterBase* CharacterBase = Cast<AITTCharacterBase>(GetOwner()))
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(CharacterBase->GetController()))
		{
			if (PlayerController != nullptr)
			{
				const FRotator Rotation = PlayerController->GetControlRotation();
				const FRotator YawRotation(0, Rotation.Yaw, 0);

				const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
				const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

				CharacterBase->AddMovementInput(ForwardDirection, MovementVector.Y);
				CharacterBase->AddMovementInput(RightDirection, MovementVector.X);
			}
		}
	}
}


// -- Sprint -- //
void UITTCharacterMovementComponent::StartSprint()
{
	FITTMovementMode SprintMode;
	if (CanSprint(SprintMode))
	{
		SetITTMovementMode(SprintMode);
	}
}

void UITTCharacterMovementComponent::StopSprint()
{
	FITTMovementMode NoneSprintMode;
	if (IsSprint(NoneSprintMode))
	{
		SetITTMovementMode(NoneSprintMode);
	}
}

bool UITTCharacterMovementComponent::CanSprint(FITTMovementMode& OutSprintMode) const
{
	int32 DataIndex = -1;
	
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

	if (static_cast<EITTAdditiveMovementMode1>(CurrentMovementMode.AdditiveMode1) != EITTAdditiveMovementMode1::None)
	{
		return false;
	}
	
	if (IsNoneSprintMode(CurrentMovementMode, DataIndex))
	{
		OutSprintMode = SprintModeDatas[DataIndex].SprintMode;
		return true;
	}

	return false;
}

bool UITTCharacterMovementComponent::IsSprint(FITTMovementMode& OutNoneSprintMode) const
{
	int32 DataIndex = -1;
	
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

	if (IsSprintMode(CurrentMovementMode, DataIndex))
	{
		OutNoneSprintMode = SprintModeDatas[DataIndex].NoneSprintMode;
		return true;
	}

	return false;
}

bool UITTCharacterMovementComponent::IsNoneSprintMode(const FITTMovementMode& InMovementMode, int32& OutDataIndex) const
{
	for (int32 i = 0; i < SprintModeDatas.Num(); ++i)
	{
		if (SprintModeDatas[i].NoneSprintMode == InMovementMode)
		{
			OutDataIndex = i;
			return true;
		}
	}

	OutDataIndex = -1;
	return false;
}

bool UITTCharacterMovementComponent::IsSprintMode(const FITTMovementMode& InMovementMode, int32& OutDataIndex) const
{
	for (int32 i = 0; i < SprintModeDatas.Num(); ++i)
	{
		if (SprintModeDatas[i].SprintMode == InMovementMode)
		{
			OutDataIndex = i;
			return true;
		}
	}

	OutDataIndex = -1;
	return false;
}

void UITTCharacterMovementComponent::OnStartSprint(int32 DataIndex)
{
	if (AITTCharacterBase* CharacterBase = Cast<AITTCharacterBase>(GetOwner()))
	{
		if (UITTCharacterStatComponent* CharacterStatComponent = CharacterBase->GetCharacterStatComponent())
		{
			EITTCharacterStat SprintSpeedStat = SprintModeDatas[DataIndex].SprintSpeedStat;
			MaxWalkSpeed = CharacterStatComponent->GetCharacterStat(SprintSpeedStat);
		}
	}
}

void UITTCharacterMovementComponent::OnStopSprint(int32 DataIndex)
{
	if (AITTCharacterBase* CharacterBase = Cast<AITTCharacterBase>(GetOwner()))
	{
		if (UITTCharacterStatComponent* CharacterStatComponent = CharacterBase->GetCharacterStatComponent())
		{
			EITTCharacterStat SprintSpeedStat = SprintModeDatas[DataIndex].NoneSprintSpeedStat;
			MaxWalkSpeed = CharacterStatComponent->GetCharacterStat(SprintSpeedStat);
		}
	}
}


// -- Falling -- //
void UITTCharacterMovementComponent::SetFallingModeToInAir()
{
	if (IsFalling())
	{
		SetITTMovementMode<EITTSubMovementMode_Falling>(EMovementMode::MOVE_Falling, EITTSubMovementMode_Falling::Falling_InAir);
	}
}

void UITTCharacterMovementComponent::PhysFalling(float deltaTime, int32 Iterations)
{
	Super::PhysFalling(deltaTime, Iterations);

	if (IsWallSlide())
	{
		if (bUseZVelotityOnlyOnWallSlide)
		{
			Velocity.X = 0;
			Velocity.Y = 0;
		}

		Velocity.Z *= ZVelocityMultiplyOnWallSlide;
	}
}

void UITTCharacterMovementComponent::OnFalling()
{
	CheckCollideWall_OnFalling();
}


// -- Jump -- //
bool UITTCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
	// Call SetITTMovementMode before the parent's to prevent changes to previous values due to duplicate calls
	if ( CharacterOwner && CharacterOwner->CanJump() )
	{
		if (!bConstrainToPlane || FMath::Abs(PlaneConstraintNormal.Z) != 1.f)
		{
			SetITTMovementMode<EITTSubMovementMode_Falling>(EMovementMode::MOVE_Falling, EITTSubMovementMode_Falling::Falling_Jump);
		}
	}
	
	return Super::DoJump(bReplayingMoves);
}


// -- Land -- //
void UITTCharacterMovementComponent::SetPostLandedPhysics(const FHitResult& Hit)
{
	// Call SetITTMovementMode before the parent's to prevent changes to previous values due to duplicate calls
	
	if( CharacterOwner )
	{
		if (!CanEverSwim() || !IsInWater())
		{
			SetITTMovementMode<EITTSubMovementMode_Walking>(EMovementMode::MOVE_Walking, EITTSubMovementMode_Walking::Walking_Landing);
		}
	}
	
	Super::SetPostLandedPhysics(Hit);
}


// -- Dash -- //
void UITTCharacterMovementComponent::Dash()
{
	if (CanDash())
	{
		DoDash();
	}
}

void UITTCharacterMovementComponent::DoDash()
{
	SetITTMovementMode<EITTSubMovementMode_Walking>(EMovementMode::MOVE_Walking, EITTSubMovementMode_Walking::Walking_Dash);
}

bool UITTCharacterMovementComponent::CanDash() const
{
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

	if (static_cast<EITTAdditiveMovementMode1>(CurrentMovementMode.AdditiveMode1) != EITTAdditiveMovementMode1::None)
	{
		return false;
	}
	
	return static_cast<EMovementMode>(CurrentMovementMode.MainMode) == EMovementMode::MOVE_Walking
		&& static_cast<EITTSubMovementMode_Walking>(CurrentMovementMode.SubMode) == EITTSubMovementMode_Walking::Walking_Jogging
		&& GetCurrentAcceleration() != FVector::Zero() && Velocity.Size2D() > 0.0f;
}

bool UITTCharacterMovementComponent::IsDash() const
{
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

	return static_cast<EMovementMode>(CurrentMovementMode.MainMode) == EMovementMode::MOVE_Walking
		&& static_cast<EITTSubMovementMode_Walking>(CurrentMovementMode.SubMode) == EITTSubMovementMode_Walking::Walking_Dash;
}


// -- Wall -- //
void UITTCharacterMovementComponent::CheckCollideWall_OnFalling()
{
	if (AITTCharacterBase* CharacterBase = Cast<AITTCharacterBase>(GetOwner()))
	{
		if (Velocity.Z <= 0.0f)
		{
			FVector ForwardOffset = CharacterBase->GetActorForwardVector() * 100.f;
		
			FHitResult OutHit_Right;
			FHitResult OutHit_Left;

			FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams::DefaultQueryParam;
			CollisionQueryParams.AddIgnoredActor(CharacterBase);
			CollisionQueryParams.bReturnPhysicalMaterial = true;

			FVector RightAttachLocation = CharacterBase->GetMesh()->GetBoneLocation(FName("RightAttach"));
			FVector LeftAttachLocation = CharacterBase->GetMesh()->GetBoneLocation(FName("LeftAttach"));

			// DrawDebugLine(GetWorld(), RightAttachLocation, RightAttachLocation + ForwardOffset, FColor::Yellow, false, 1.f, 0, 1);
			// DrawDebugLine(GetWorld(), LeftAttachLocation, LeftAttachLocation + ForwardOffset, FColor::Yellow, false, 1.f, 0, 1);
			
			if (GetWorld()->LineTraceSingleByChannel(OutHit_Right, RightAttachLocation, RightAttachLocation + ForwardOffset, ECollisionChannel::ECC_WorldStatic, CollisionQueryParams))
			{
				if (GetWorld()->LineTraceSingleByChannel(OutHit_Left, LeftAttachLocation, LeftAttachLocation + ForwardOffset, ECollisionChannel::ECC_WorldStatic, CollisionQueryParams))
				{
					if (OutHit_Right.GetActor() == OutHit_Left.GetActor())
					{
						ITTLOG(Warning, TEXT("[%s] HitActor : %s"), *ITTSTRING_FUNC, *OutHit_Right.GetActor()->GetName());

						// Transform
						AttachCharacterTransformTo(RightAttachLocation, LeftAttachLocation, OutHit_Left.ImpactPoint, OutHit_Right.ImpactPoint);
						
						// -- Up -- //
						FHitResult OutHit_Right_Up;
						FHitResult OutHit_Left_Up;
						
						FVector RightAttachLocation_Up = RightAttachLocation + FVector(0.f, 0.f, 30.f);
						FVector LeftAttachLocation_Up = LeftAttachLocation + FVector(0.f, 0.f, 30.f);

						//DrawDebugLine(GetWorld(), RightAttachLocation_Up, RightAttachLocation_Up + ForwardOffset, FColor::Red, false, 1.f, 0, 1);
						//DrawDebugLine(GetWorld(), LeftAttachLocation_Up, LeftAttachLocation_Up + ForwardOffset, FColor::Red, false, 1.f, 0, 1);
						
						if (!GetWorld()->LineTraceSingleByChannel(OutHit_Right_Up, RightAttachLocation_Up, RightAttachLocation_Up + ForwardOffset, ECollisionChannel::ECC_WorldStatic, CollisionQueryParams))
						{
							if (!GetWorld()->LineTraceSingleByChannel(OutHit_Left_Up, LeftAttachLocation_Up, LeftAttachLocation_Up + ForwardOffset, ECollisionChannel::ECC_WorldStatic, CollisionQueryParams))
							{
								if (!IsLedgeGrab())
								{
									LedgeGrab(OutHit_Right.PhysMaterial);
									return;
								}
							}
						}
						// -------- //
						
						if (!IsWallSlide())
						{
							WallSlide(OutHit_Right.PhysMaterial);
						}

						return;
					}
				}
			}
		}
	}

	// if (IsWallSlide())
	// {
	// 	SetFallingModeToInAir();
	// }
}


// -- Wall Slide -- //
void UITTCharacterMovementComponent::WallSlide(TWeakObjectPtr<UPhysicalMaterial> PhysicalMaterial)
{
	if (CanWallSlide(PhysicalMaterial))
	{
		SetITTMovementMode<EITTSubMovementMode_Falling>(EMovementMode::MOVE_Falling, EITTSubMovementMode_Falling::Falling_WallSlide);
	}
}

void UITTCharacterMovementComponent::OnStartWallSlide()
{
}

void UITTCharacterMovementComponent::OnStopWallSlide()
{
}

bool UITTCharacterMovementComponent::CanWallSlide(TWeakObjectPtr<UPhysicalMaterial> PhysicalMaterial) const
{
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

	if (static_cast<EITTAdditiveMovementMode1>(CurrentMovementMode.AdditiveMode1) != EITTAdditiveMovementMode1::None)
	{
		return false;
	}
	
	if (PhysicalMaterial != nullptr)
	{
		return PhysicalMaterial->SurfaceType == EPhysicalSurface::SurfaceType1
		|| PhysicalMaterial->SurfaceType == EPhysicalSurface::SurfaceType2
		|| PhysicalMaterial->SurfaceType == EPhysicalSurface::SurfaceType30;
	}

	return false;
}

bool UITTCharacterMovementComponent::IsWallSlide() const
{
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

	return IsWallSlideMode(CurrentMovementMode);
}

bool UITTCharacterMovementComponent::IsWallSlideMode(const FITTMovementMode& InMovementMode) const
{
	return InMovementMode.MainMode == static_cast<uint8>(EMovementMode::MOVE_Falling)
	&& InMovementMode.SubMode == static_cast<uint8>(EITTSubMovementMode_Falling::Falling_WallSlide);
}


// -- Ledge Grab -- //
void UITTCharacterMovementComponent::LedgeGrab(TWeakObjectPtr<UPhysicalMaterial> PhysicalMaterial)
{
	if (CanLedgeGrab(PhysicalMaterial))
	{
		SetITTMovementMode<EITTSubMovementMode_Custom>(EMovementMode::MOVE_Custom, EITTSubMovementMode_Custom::Custom_LedgeGrab);
	}
}

void UITTCharacterMovementComponent::OnStartLedgeGrab()
{
}

void UITTCharacterMovementComponent::OnStopLedgeGrab()
{
}

bool UITTCharacterMovementComponent::CanLedgeGrab(TWeakObjectPtr<UPhysicalMaterial> PhysicalMaterial) const
{
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

	if (static_cast<EITTAdditiveMovementMode1>(CurrentMovementMode.AdditiveMode1) != EITTAdditiveMovementMode1::None)
	{
		return false;
	}
	
	if (PhysicalMaterial != nullptr)
	{
		return PhysicalMaterial->SurfaceType == EPhysicalSurface::SurfaceType1
		|| PhysicalMaterial->SurfaceType == EPhysicalSurface::SurfaceType2
		|| PhysicalMaterial->SurfaceType == EPhysicalSurface::SurfaceType30;
	}

	return false;
}

bool UITTCharacterMovementComponent::IsLedgeGrab() const
{
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

	return IsLedgeGrabMode(CurrentMovementMode);
}

bool UITTCharacterMovementComponent::IsLedgeGrabMode(const FITTMovementMode& InMovementMode) const
{
	return InMovementMode.MainMode == static_cast<uint8>(EMovementMode::MOVE_Custom)
		&& InMovementMode.SubMode == static_cast<uint8>(EITTSubMovementMode_Custom::Custom_LedgeGrab);
}


// -- PickUp -- //
void UITTCharacterMovementComponent::PickUp(TObjectPtr<AActor> Target)
{
	if (!IsValid(Target))
	{
		return;
	}
	
	if (CanPickUp(Target))
	{
		PickUpTarget = Target;
		SetITTMovementMode<EITTSubMovementMode_Custom>(EMovementMode::MOVE_Custom, EITTSubMovementMode_Custom::Custom_PickUp, EITTAdditiveMovementMode1::PickUp);
	}
}

void UITTCharacterMovementComponent::OnStartPickUp()
{
	if (AITTCharacterBase* CharacterBase = Cast<AITTCharacterBase>(GetOwner()))
	{
		if (IsValid(PickUpTarget))
		{
			CharacterBase->JumpMaxCount = 1;
			
			PickUpTarget->AttachToActor(CharacterBase, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
}

void UITTCharacterMovementComponent::OnStopPickUp()
{
	if (AITTCharacterBase* CharacterBase = Cast<AITTCharacterBase>(GetOwner()))
	{
		CharacterBase->JumpMaxCount = 2;
		
		if (IsValid(PickUpTarget))
		{
			PickUpTarget->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			TArray<UActorComponent*> ForcedComponents = PickUpTarget->GetComponentsByTag(UPrimitiveComponent::StaticClass(), FName("PickUpForced"));
		
			if (ForcedComponents.IsValidIndex(0))
			{
				UPrimitiveComponent* ForcedComponent = Cast<UPrimitiveComponent>(ForcedComponents[0]);
				ForcedComponent->AddImpulse(FVector(100.f, 100.f, 100.f));
			}
			else
			{
				ITTLOG(Error, TEXT("Tag 'PickUpForced' To PickUpTarget's Primitive Component."));
			}
		
			PickUpTarget = nullptr;
		}
	}
}

bool UITTCharacterMovementComponent::CanPickUp(TObjectPtr<AActor> Target) const
{
	if (IsPickUp())
	{
		return false;
	}
	
	return true;
}

bool UITTCharacterMovementComponent::IsPickUp() const
{
	FITTMovementMode CurrentMovementMode(static_cast<uint32>(MovementModeMachine->GetCurrentStateId()));

	return CurrentMovementMode.AdditiveMode1 == static_cast<uint8>(EITTAdditiveMovementMode1::PickUp);
}

bool UITTCharacterMovementComponent::IsPickUpMode(const FITTMovementMode& InMovementMode) const
{
	return InMovementMode.AdditiveMode1 == static_cast<uint8>(EITTAdditiveMovementMode1::PickUp);
}
// ============================== //


// ========== Character Transform ========== //
void UITTCharacterMovementComponent::AttachCharacterTransformTo(const FVector& BasePoint1,
	const FVector& BasePoint2, const FVector& TargetPoint1, const FVector& TargetPoint2)
{
	if (AITTCharacterBase* CharacterBase = Cast<AITTCharacterBase>(GetOwner()))
	{
		float Angle = 0.f;
		FVector Vector = FVector::Zero();
		
		UITTUtilityFunctionLibrary::CalculateMovingValue_TwoPointsToProjectionPoint(Angle, Vector,
			BasePoint1, BasePoint2, TargetPoint1, TargetPoint2);

		CharacterBase->AddActorWorldRotation(FRotator(0.f, Angle, 0.f), true);
		CharacterBase->SetActorLocation(CharacterBase->GetActorLocation() + Vector, true);
	}
}
// ========================================= //