// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_Ch1_Start.h"


UITTScene_Ch1_Start::UITTScene_Ch1_Start()
{
}


void UITTScene_Ch1_Start::Initialize(EITTSceneType _SceneType)
{
	Super::Initialize(_SceneType);

	SetCamera();
}

void UITTScene_Ch1_Start::Finalize()
{
	Super::Finalize();
}

void UITTScene_Ch1_Start::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Camera ========== //
void UITTScene_Ch1_Start::SetCamera()
{
}
// ============================ //
