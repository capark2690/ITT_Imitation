// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/ITTPawn.h"
#include "ITTPawn_CharacterSelect.generated.h"

UCLASS()
class ITT_API AITTPawn_CharacterSelect : public AITTPawn
{
	GENERATED_BODY()

public:
	AITTPawn_CharacterSelect();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


	// ========== Input ========== //
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// =========================== //


	// ==================== Getter ==================== //
	// ========== Component ========== //
	// -- Input -- //
	class UITTInputHelperComponent_GUI* GetInputHelperComponent_GUI() const { return InputHelperComponent_GUI; }
	// =============================== //
	// ================================================ //
	
	
protected:
	// ========== Component ========== //
	// -- Input -- //
	UPROPERTY(Category = ITTComponent, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UITTInputHelperComponent_GUI> InputHelperComponent_GUI;
	// =============================== //
};
