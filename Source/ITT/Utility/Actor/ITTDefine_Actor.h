// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTDefine_Actor.generated.h"


// ==================== Enum ==================== //
// ========== Switch ========== //
UENUM(BlueprintType)
enum class EITTSwitchConditionTriggerType : uint8
{
	None,

	TriggerFromOther,
	ChangeInteractorCharacterMovementMode,
};

UENUM(BlueprintType)
enum class EITTSwitchExecuteType : uint8
{
	None,

	ChangeScene,
	ActiveOtherComponent,
	PlaySequence,
};
// ============================== //
// ============================================== //


// ==================== Struct ==================== //
// ========== Switch ========== //
USTRUCT(Blueprintable)
struct FITTSwitchTriggerData
{
	GENERATED_BODY()
	
	FITTSwitchTriggerData()
	{
	}
	
	UPROPERTY(Category=ITT, EditAnywhere)
	float Time;

	UPROPERTY(Category=ITT, EditAnywhere)
	FName SwitchTag;

	UPROPERTY(Category=ITT, EditAnywhere)
	FName SwitchConditionKey;

	UPROPERTY(Category=ITT, EditAnywhere)
	bool bSatisfy;
};

USTRUCT(Blueprintable)
struct FITTSwitchCondition
{
	GENERATED_BODY()

	FITTSwitchCondition()
	{
	}
	
	UPROPERTY(Category=ITT, EditAnywhere)
	class UITTData_SwitchCondition* OnConditionData;
	
	UPROPERTY(Category=ITT, EditAnywhere)
	class UITTData_SwitchCondition* OffConditionData;
};
// ============================== //


// ========== Rotation ========== //
USTRUCT(Blueprintable)
struct FITTRotationPhaseData
{
	GENERATED_BODY()

	FITTRotationPhaseData()
		: PhaseTime(-1.f), Count(1), Time_ForCount(1.f), RotationValue_ForCount(FRotator::ZeroRotator)
	{
	}


	UPROPERTY(Category=ITT, EditAnywhere)
	float PhaseTime;
	
	UPROPERTY(Category=ITT, EditAnywhere)
	int32 Count;
	
	UPROPERTY(Category=ITT, EditAnywhere)
	float Time_ForCount;
	
	UPROPERTY(Category=ITT, EditAnywhere)
	FRotator RotationValue_ForCount;
};

USTRUCT(Blueprintable)
struct FITTRotationData
{
	GENERATED_BODY()

	FITTRotationData()
	{
	}

	
	UPROPERTY(Category=ITT, EditAnywhere)
	TArray<FITTRotationPhaseData> RotatioPhases;
};
// ============================== //
// ================================================ //


// ==================== Delegate ==================== //
// ========== Component ========== //
DECLARE_DELEGATE(FITTActorComponentActiveDelegate);
DECLARE_DELEGATE(FITTActorComponentDeactiveDelegate);

DECLARE_MULTICAST_DELEGATE_TwoParams(FITTOnActorComponentInteractDelegate, class UPrimitiveComponent*, class AITTCharacterBase*);
// =============================== //
// ================================================== //