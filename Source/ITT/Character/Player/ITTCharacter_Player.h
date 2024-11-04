// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ITTCharacterBase.h"
#include "ITTCharacter_Player.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTCharacter_Player : public AITTCharacterBase
{
	GENERATED_BODY()

public:
	AITTCharacter_Player(const FObjectInitializer& ObjectInitializer);

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


	// ========== Input ========== //
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// =========================== //


	// ========== Camera ========== //
	virtual void SetCameraSettings(class UITTData_CameraSettings* Data_CameraSettings);
	// ============================ //


protected:
	// ========== Movement ========== //
	// -- Jump -- //
	virtual bool CanJumpInternal_Implementation() const override;
	// ============================== //

	
public:
	// ==================== Getter ==================== //
	// ========== Component ========== //
	// -- Camera -- //
	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	// -- Input -- //
	class UITTInputHelperComponent* GetInputHelperComponent() const { return InputHelperComponent; }
	// =============================== //
	// ================================================ //

	
protected:
	// ========== Component ========== //
	// -- Camera -- //
	UPROPERTY(Category = ITTComponent, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> CameraBoom;
	
	UPROPERTY(Category = ITTComponent, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> FollowCamera;
	
	
	// -- Input -- //
	UPROPERTY(Category = ITTComponent, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UITTInputHelperComponent> InputHelperComponent;
	// =============================== //
};