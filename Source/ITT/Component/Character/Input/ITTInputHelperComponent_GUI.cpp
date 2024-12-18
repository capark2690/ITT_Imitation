﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTInputHelperComponent_GUI.h"

#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"


UITTInputHelperComponent_GUI::UITTInputHelperComponent_GUI()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UITTInputHelperComponent_GUI::BeginPlay()
{
	Super::BeginPlay();
}


// ========== Input ========== //
void UITTInputHelperComponent_GUI::SetupPlayerInputComponent(UInputComponent* _PlayerInputComponent)
{
	// Add Input Mapping Context
	if (GetOwner())
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetOwner()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(MappingContext, 0);
			}
		}
	}
}
// =========================== //
