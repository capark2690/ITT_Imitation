// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Data/Table/ITTTableBase.h"
#include "Styling/SlateBrush.h"
#include "InputCoreTypes.h"
#include "ITTTable_Key.generated.h"

/**
 * 
 */
USTRUCT()
struct FITTTableRow_Key : public FTableRowBase
{
	GENERATED_BODY()

	FITTTableRow_Key()
	{
	}

	UPROPERTY(EditAnywhere)
	FSlateBrush SlateBrush_Bg;
	
	UPROPERTY(EditAnywhere)
	FSlateBrush SlateBrush_Key;
};


UCLASS()
class ITT_API UITTTable_Key : public UITTTableBase
{
	GENERATED_BODY()

public:
	static FName GetTableName() { return FName(TableName); }

	
	UITTTable_Key();

	
	// ========== Key ========== //
	void GetKeyBrush(const FKey& InKey, FSlateBrush& OutSlateBrush_Bg, FSlateBrush& OutSlateBrush_Key) const;
	// ========================= //

	
private:
	static constexpr char TableName[] = "DT_Key";
};
