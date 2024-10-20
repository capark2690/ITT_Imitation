// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_LocalPlay_SelectInput.h"

#include "GameBase/GameManager/GameBase/ITTSceneManager.h"


UITTScene_LocalPlay_SelectInput::UITTScene_LocalPlay_SelectInput()
{
}


void UITTScene_LocalPlay_SelectInput::Initialize(EITTSceneType _SceneType)
{
	Super::Initialize(_SceneType);

	// Temp
	if (SceneMgr)
	{
		SceneMgr->ChangeScene(EITTSceneType::LocalPlay_SelectCharacter, EITTLoadingType::None, true);
	}
}

void UITTScene_LocalPlay_SelectInput::BeginPlay()
{
	Super::BeginPlay();
}

void UITTScene_LocalPlay_SelectInput::Finalize()
{
	Super::Finalize();
}

void UITTScene_LocalPlay_SelectInput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
