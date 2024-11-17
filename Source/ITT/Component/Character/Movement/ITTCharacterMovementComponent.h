// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/ITTDefine_Character.h"
#include "ITTCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UITTCharacterMovementComponent();

	
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	
	// ========== Movement Mode Machine ========== //
	void CreateMovementModeMachine();

	void DestroyMovementModeMachine();
	
	virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0) override;

	virtual void SetITTMovementMode(FITTMovementMode ITTMovementMode, bool bChangeImmediately = true);
	
	virtual void SetITTMovementMode(uint8 MainMode,  uint8 SubMode = 0, uint8 AdditiveMode1 = 0, uint8 AdditiveMode2 = 0, bool bChangeImmediately = true);

	template<typename T>
	void SetITTMovementMode(EMovementMode MainMode,  T SubMode, uint8 AdditiveMode1 = 0, uint8 AdditiveMode2 = 0, bool bChangeImmediately = true)
	{
		SetITTMovementMode(static_cast<uint8>(MainMode), static_cast<uint8>(SubMode), AdditiveMode1, AdditiveMode2, bChangeImmediately);
	}


	// -- OnChange -- //
	UFUNCTION()
	virtual void OnChangeMovementMode(int64 PreviousMovementModeId, int64 CurrentMovementModeId);
	// =========================================== //


	// ========== Body ========== //
	// -- Init -- //
	virtual void InitializeBodyInstance();
	// ========================== //
	
	
	// ========== Movement ========== //
	// -- Init -- //
	virtual void InitializeMovementValue();


	// -- Move -- //
	virtual void Move(FVector2d MovementVector);

	
	// -- Sprint -- //
	virtual void StartSprint();

	virtual void StopSprint();
	
	virtual bool CanSprint(FITTMovementMode& OutSprintMode) const;

	virtual bool IsSprint(FITTMovementMode& OutNoneSprintMode) const;

	virtual bool IsNoneSprintMode(const FITTMovementMode& InMovementMode, int32& OutDataIndex) const;
	
	virtual bool IsSprintMode(const FITTMovementMode& InMovementMode, int32& OutDataIndex) const;
	
	virtual void OnStartSprint(int32 DataIndex);

	virtual void OnStopSprint(int32 DataIndex);


	// -- Falling -- //
	virtual void SetFallingModeToInAir();
	
	virtual void PhysFalling(float deltaTime, int32 Iterations) override;

	virtual void OnFalling();

	
	// -- Jump -- //
	virtual bool DoJump(bool bReplayingMoves) override;

	
public:
	// -- Dash -- //
	virtual void Dash();
	
	virtual void DoDash();
	
	virtual bool CanDash() const;

	virtual bool IsDash() const;


	// -- Wall -- //
	virtual void CheckCollideWall_OnFalling();

	
	// -- Wall Slide -- //
	virtual void WallSlide(TWeakObjectPtr<UPhysicalMaterial> PhysicalMaterial);
	
	virtual void OnStartWallSlide();
	
	virtual void OnStopWallSlide();
	
	virtual bool CanWallSlide(TWeakObjectPtr<UPhysicalMaterial> PhysicalMaterial) const;
	
	virtual bool IsWallSlide() const;

	virtual bool IsWallSlideMode(const FITTMovementMode& InMovementMode) const;


	// -- Ledge Grab -- //
	virtual void LedgeGrab(TWeakObjectPtr<UPhysicalMaterial> PhysicalMaterial);
	
	virtual void OnStartLedgeGrab();
	
	virtual void OnStopLedgeGrab();
	
	virtual bool CanLedgeGrab(TWeakObjectPtr<UPhysicalMaterial> PhysicalMaterial) const;
	
	virtual bool IsLedgeGrab() const;

	virtual bool IsLedgeGrabMode(const FITTMovementMode& InMovementMode) const;
	// ============================== //


	// ========== Character Transform ========== //
	virtual void AttachCharacterTransformTo(const FVector& BasePoint1, const FVector& BasePoint2,
		const FVector& TargetPoint1, const FVector& TargetPoint2);
	// ========================================= //
	
	
	// ==================== Getter ==================== //
	// ========== Movement Mode Machine ========== //
	class UITTStateMachine* GetMovementModeMachine() const { return MovementModeMachine; }
	// =========================================== //
	// ================================================ //

	
protected:
	// ========== Movement Mode Machine ========== //
	TObjectPtr<class UITTStateMachine> MovementModeMachine;
	// =========================================== //


	// ========== Body ========== //
	// -- Init -- //
	FBodyInstance* LeftHandThumb;
	FBodyInstance* RightHandThumb;
	// ========================== //

	
	// ========== Movement ========== //
	// -- Sprint -- //
	UPROPERTY(Category="ITT|Sprint", EditAnywhere)
	TArray<FITTSprintModeData> SprintModeDatas;


	// -- WallSlide -- //
	UPROPERTY(Category="ITT|WallSlide", EditAnywhere)
	bool bUseZVelotityOnlyOnWallSlide;
	
	UPROPERTY(Category="ITT|WallSlide", EditAnywhere)
	float ZVelocityMultiplyOnWallSlide;
	// ============================== //
};