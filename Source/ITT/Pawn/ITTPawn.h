// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ITTPawn.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTPawn : public APawn
{
	GENERATED_BODY()

public:
	AITTPawn();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


	// ========== Input ========== //
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// =========================== //
};
