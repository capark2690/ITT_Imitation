// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ITTUtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// ========== Convert Enum ========== //
	static FString ConvertEnumToString(const FString& EnumName, int64 EnumValue);
	static FName ConvertEnumToName(const FString& EnumName, int64 EnumValue);

	template<typename T>
	static FString ConvertEnumToString(const FString& EnumName, T EnumValue)
	{
		return ConvertEnumToString(EnumName, static_cast<int64>(EnumValue));
	}
	
	template<typename T>
	static FName ConvertEnumToName(const FString& EnumName, T EnumValue)
	{
		return ConvertEnumToName(EnumName, static_cast<int64>(EnumValue));
	}
	// ================================== //


	// ========== Math ========== //
	static float CalculateMiddleAngle(FVector BaseVector, FVector TargetVector, bool bCalulateOnly2D = false);
	
	static void CalculateMovingValue_TwoPointsToProjectionPoint(float& OutAngle, FVector& OutVector,
		const FVector& InBasePoint1, const FVector& InBasePoint2, const FVector& InTargetPoint1,
		const FVector& InTargetPoint2);
	// ========================== //
};