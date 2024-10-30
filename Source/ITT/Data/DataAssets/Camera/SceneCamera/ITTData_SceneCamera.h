// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ITTData_SceneCamera.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTData_SceneCamera : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bForceDisableSplitscreen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bViewTargetPlayer1IsPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bViewTargetPlayer2IsPawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ViewTargetName_Player1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ViewTargetName_Player2;
};
