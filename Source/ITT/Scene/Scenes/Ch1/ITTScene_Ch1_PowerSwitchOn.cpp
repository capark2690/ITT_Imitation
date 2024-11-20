// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_Ch1_PowerSwitchOn.h"


UITTScene_Ch1_PowerSwitchOn::UITTScene_Ch1_PowerSwitchOn()
{
	SequenceName = FName("PowerSwitchOn");
}


void UITTScene_Ch1_PowerSwitchOn::Initialize(EITTSceneType _SceneType, FITTTableRow_Scene* _SceneRow)
{
	Super::Initialize(_SceneType, _SceneRow);
}

void UITTScene_Ch1_PowerSwitchOn::Finalize()
{
	Super::Finalize();
}

void UITTScene_Ch1_PowerSwitchOn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}