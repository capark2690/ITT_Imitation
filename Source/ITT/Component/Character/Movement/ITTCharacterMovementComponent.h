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

	
	// -- Jump -- //
	virtual bool DoJump(bool bReplayingMoves) override;
	
	virtual void OnFalling();


	// -- Dash -- //
	virtual void Dash();
	
	virtual void DoDash();
	
	virtual bool CanDash() const;

	virtual bool IsDash() const;


	// -- Wall -- //
	virtual void CheckCollideWall_OnFalling();

	
	// -- Wall Slide -- //
	virtual void WallSlide();
	
	virtual void OnStartWallSlide();
	
	virtual void OnStopWallSlide();
	
	virtual bool CanWallSlide() const;
	
	virtual bool IsWallSlide() const;

	virtual bool IsWallSlideMode(const FITTMovementMode& InMovementMode) const;
	// ============================== //

	
	// ==================== Getter ==================== //
	// ========== Movement Mode Machine ========== //
	class UITTStateMachine* GetMovementModeMachine() { return MovementModeMachine; }
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
	// ============================== //
};