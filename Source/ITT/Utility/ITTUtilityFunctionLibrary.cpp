// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTUtilityFunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"


// ========== Convert Enum ========== //
FString UITTUtilityFunctionLibrary::ConvertEnumToString(const FString& EnumName, int64 EnumValue)
{
	UEnum* Enum = FindObject<UEnum>(nullptr, *EnumName);
	return Enum ? Enum->GetNameStringByValue(EnumValue) : FString();
}

FName UITTUtilityFunctionLibrary::ConvertEnumToName(const FString& EnumName, int64 EnumValue)
{
	UEnum* Enum = FindObject<UEnum>(nullptr, *EnumName);
	return Enum ? Enum->GetNameByValue(EnumValue) : FName();
}
// ================================== //


// ========== Math ========== //
float UITTUtilityFunctionLibrary::CalculateMiddleAngle(FVector BaseVector, FVector TargetVector, bool bCalulateOnly2D)
{
	if (bCalulateOnly2D)
	{
		BaseVector.Z = 0.f;
		TargetVector.Z = 0.f;
	}
	
	//내적 후 아크 코사인을 통해 각을 구함 (0~180)
	float InnerProduct = FVector::DotProduct(BaseVector,TargetVector);
	float Degree = UKismetMathLibrary::DegAcos(InnerProduct);
    
	//외적으로 표면 벡터를 구해 Z의 값으로 부호를 구함
	FVector OutProduct = FVector::CrossProduct(BaseVector, TargetVector);
	float Sign = UKismetMathLibrary::SignOfFloat(OutProduct.Z);
    
	return Degree*Sign;
}

void UITTUtilityFunctionLibrary::CalculateMovingValue_TwoPointsToProjectionPoint(float& OutAngle, FVector& OutVector,
	const FVector& InBasePoint1, const FVector& InBasePoint2, const FVector& InTargetPoint1,
	const FVector& InTargetPoint2)
{
	FVector Diff_P1 = InTargetPoint1 - InBasePoint1;
	FVector Diff_P2 = InTargetPoint2 - InBasePoint2;
	FVector Diff_P1ToP2 = InBasePoint2 - InBasePoint1;

	float X = Diff_P1ToP2.Length();
	float H = Diff_P2.Length() - Diff_P1.Length();

	OutAngle = - UKismetMathLibrary::DegAtan2(H , X);

	OutVector = (Diff_P1 + Diff_P2) / 2;
}
// ========================== //
