// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/RootAnimation/ITTRootAnimInstance.h"
#include "Character/ITTDefine_Character.h"
#include "ITTRootAnimInstance_Character.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTRootAnimInstance_Character : public UITTRootAnimInstance
{
	GENERATED_BODY()

public:
	UITTRootAnimInstance_Character();

	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;
	virtual void NativeUninitializeAnimation() override;
	virtual void NativeBeginPlay() override;

	
private:
	void InitializeOwner();
	
	void InitializeOwnerComponent();

	
protected:
	// ========== Movement Mode ========== //
	virtual void UpdateCharacterMovementMode();
	// =================================== //
	
	
	// ========== SubAnimation ========== //
	virtual void UpdateSubAnimation();

	TSubclassOf<UAnimInstance> GetSubAnimInstanceClass(const FITTMovementMode& MovementMode) const;
	// ================================== //

	
protected:
	TWeakObjectPtr<class AITTCharacterBase> CharacterBase;

	TWeakObjectPtr<class UITTAnimationHelperComponent> AnimationHelperComponent;
	
	TWeakObjectPtr<class UITTCharacterMovementComponent> CharacterMovementComponent;

	TWeakObjectPtr<class UITTStateMachine> MovementModeMachine;

	
	// ========== Movement Mode ========== //
	UPROPERTY(Category = ITT, BlueprintReadOnly)
	FITTMovementMode CurrentMovementMode;
	// =================================== //
};
