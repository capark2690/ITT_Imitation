﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTGameModeBase.h"
#include "ITTGameMode_Title.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTGameMode_Title : public AITTGameModeBase
{
	GENERATED_BODY()

public:
	AITTGameMode_Title();

	
protected:
	virtual void BeginPlay() override;

	
protected:
	// ========== Player ========== //
	virtual void AdjustPlayer();
	// ============================ //


private:
	// ========== Player ========== //
	const int32 LocalPlayerNum = 2;
	// ============================ //
};