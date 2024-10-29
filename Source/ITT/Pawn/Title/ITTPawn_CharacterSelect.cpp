// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTPawn_CharacterSelect.h"

#include "Component/Character/Input/ITTInputHelperComponent_GUI.h"


AITTPawn_CharacterSelect::AITTPawn_CharacterSelect()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create input helper component
	InputHelperComponent_GUI = CreateDefaultSubobject<UITTInputHelperComponent_GUI>(TEXT("InputHelperComponent_GUI"));
}


void AITTPawn_CharacterSelect::BeginPlay()
{
	Super::BeginPlay();
	
}

void AITTPawn_CharacterSelect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Input ========== //
void AITTPawn_CharacterSelect::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (InputHelperComponent_GUI)
	{
		InputHelperComponent_GUI->SetupPlayerInputComponent(PlayerInputComponent);
	}
}
// =========================== //
