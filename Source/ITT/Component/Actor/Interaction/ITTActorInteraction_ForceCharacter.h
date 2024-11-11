// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actor/ITTDefine_Actor.h"
#include "Character/ITTDefine_Character.h"
#include "ITTActorInteraction_ForceCharacter.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=ITTComponent, meta=(BlueprintSpawnableComponent))
class ITT_API UITTActorInteraction_ForceCharacter : public UActorComponent
{
	GENERATED_BODY()

public:
	UITTActorInteraction_ForceCharacter();


	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	

	// ========== Interact ========== //
	virtual void RegisterBindCollisionComponents();
	
	virtual void BindInteractEvent();

	UFUNCTION()
	virtual void OnInteract(class UPrimitiveComponent* _InteractionCollision, class AITTCharacterBase* _InteractorCharacter);
	// ============================= //


	// ========== Force Character ========== //
	virtual void ForceChangeCharacterMovementMode(float Time);
	
	virtual void ForceChangeCharacterLocation(float Time);
	
	virtual void ForceChangeCharacterRocation(float Time);
	// ===================================== //


	// ========== Switch ========== //
	virtual void CheckTriggerSwitch(float Time);
	// ============================ //

	
protected:
	// ========== Bind Collision ========== //
	UPROPERTY(Category="ITT|BindCollision", EditAnywhere)
	TArray<FName> BindCollisionTags;

	UPROPERTY()
	TArray<TWeakObjectPtr<class UPrimitiveComponent>> BindCollisionComponents;
	// ==================================== //

	
	// ========== Switch ========== //
	UPROPERTY(Category="ITT|Switch", EditAnywhere)
	TArray<FITTSwitchTriggerData> SwitchTriggerData;

	UPROPERTY()
	int32 SwitchTriggerDataIndex;
	// ============================ //

	
	// ========== Interactor ========== //
	TWeakObjectPtr<class AITTCharacterBase> InteractorCharacter;

	TWeakObjectPtr<class UITTCharacterMovementComponent> InteractorMovementComponent;
	
	TWeakObjectPtr<class UPrimitiveComponent> InteractionCollision;
	// ================================ //

	
	// ========== Interaction Time ========== //
	UPROPERTY()
	bool bActiveInteraction;
	
	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	float MaxTime;

	UPROPERTY()
	float ElapsedTime;
	// ====================================== //

	
	// ========== Force Character ========== //
	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	bool bChange_CharacterMovementMode;
	
	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	TArray<FITTChangeValue_CharacterMovementMode> ChangeValues_CharacterMovementMode;

	UPROPERTY()
	int32 MovementChangeValueIndex;
	
	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	bool bChange_Location_Static;

	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	FVector StaticValues_Location;
	
	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	bool bChange_Location_Curve;
	
	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	class UCurveVector* ChangeCurve_Location;

	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	bool bChange_Rotation_Static;

	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	FRotator StaticValues_Rotation;
	
	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	bool bChange_Rotation_Curve;
	
	UPROPERTY(Category="ITT|ChangeValue", EditAnywhere)
	class UCurveVector* ChangeCurve_Rotation;
	// ===================================== //
};
