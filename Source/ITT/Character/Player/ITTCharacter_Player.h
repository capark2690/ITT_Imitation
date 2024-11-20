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

protected:
	virtual void CheckInfraredCamera();
	// ============================ //


public:
	// ========== Movement ========== //
	// -- Jump -- //
	virtual void Jump() override;

protected:
	virtual bool CanJumpInternal_Implementation() const override;
	// ============================== //

	
public:
	EITTPlayerCharacterType GetCharacterType() const { return CharacterType; }

	
	// ========== Component ========== //
	// -- Camera -- //
	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	// -- Input -- //
	class UITTInputHelperComponent* GetInputHelperComponent() const { return InputHelperComponent; }


	// -- Interaction -- //
	class UITTPlayerInteractionComponent* GetPlayerInteractionComponent() const { return PlayerInteractionComponent; }
	// =============================== //

	
protected:
	UPROPERTY(Category = ITT, EditAnywhere, BlueprintReadOnly)
	EITTPlayerCharacterType CharacterType;

	
	// ========== Component ========== //
	// -- Camera -- //
	UPROPERTY(Category = ITTComponent, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> CameraBoom;
	
	UPROPERTY(Category = ITTComponent, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> FollowCamera;
	
	
	// -- Input -- //
	UPROPERTY(Category = ITTComponent, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UITTInputHelperComponent> InputHelperComponent;


	// -- Interaction -- //
	UPROPERTY(Category = ITTComponent, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UITTPlayerInteractionComponent> PlayerInteractionComponent;
	// =============================== //


	UPROPERTY(Category = ITTComponent, EditAnywhere)
	TMap<FName, TScriptInterface<class IBlendableInterface>> InfraredCameraMaterials;
};