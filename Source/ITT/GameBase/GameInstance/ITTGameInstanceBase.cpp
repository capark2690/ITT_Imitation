﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTGameInstanceBase.h"

#include "Engine/World.h"

#include "GameBase/BasicUtility/ITTBasicUtility.h"

#include "GameBase/GameManager/ITTSingletonManager.h"
#include "GameBase/GameManager/GameBase/ITTLevelManager.h"


UITTGameInstanceBase::UITTGameInstanceBase()
{
	FWorldDelegates::OnStartGameInstance.AddUObject(this, &UITTGameInstanceBase::OnStartGameInstance);
}

UITTGameInstanceBase::~UITTGameInstanceBase()
{
	FWorldDelegates::OnStartGameInstance.RemoveAll(this);
}


void UITTGameInstanceBase::Init()
{
	Super::Init();

	ProcessInitialize();
	ITTCHECK(LaunchProcess == EITTLaunchProcess::ProcessFinished);
}

void UITTGameInstanceBase::Shutdown()
{
	ProcessFinalize();
	
	Super::Shutdown();
}

void UITTGameInstanceBase::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
}

void UITTGameInstanceBase::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);

	if (IsValid(LevelMgr))
	{
		LevelMgr->LoadLevelComplete();
	}
}

bool UITTGameInstanceBase::Tick(float DeltaSeconds)
{
	if (LaunchProcess == EITTLaunchProcess::ProcessFinished)
	{
		LaunchProcess = EITTLaunchProcess::End;
	}

	TickGameManagers(DeltaSeconds);
	
	return true;
}

void UITTGameInstanceBase::OnStartGameInstance(UGameInstance* GameInstance)
{
	InitializeGameManagers();
}


// ==========  Launch Process ========== //
void UITTGameInstanceBase::ProcessInitialize()
{
	LaunchProcess = EITTLaunchProcess::CreateBasicUtility;
	if (CreateBasicUtility() == false)
	{
		return;
	}
	
	LaunchProcess = EITTLaunchProcess::CreateGameManager;
	if (CreateGameManagers() == false)
	{
		return;
	}
	
	LaunchProcess = EITTLaunchProcess::RegisterTick;
	if (RegisterTick() == false)
	{
		return;
	}
	
	LaunchProcess = EITTLaunchProcess::ProcessFinished;
}

void UITTGameInstanceBase::ProcessFinalize()
{
	if (LaunchProcess > EITTLaunchProcess::RegisterTick)
	{
		UnregisterTick();
	}

	if (LaunchProcess > EITTLaunchProcess::CreateGameManager)
	{
		DestroyGameManagers();
	}

	if (LaunchProcess > EITTLaunchProcess::CreateBasicUtility)
	{
		DestroyBasicUtility();
	}
}

bool UITTGameInstanceBase::CreateBasicUtility()
{
	if (TObjectPtr<UITTBasicUtility> BasicUtility = UITTBasicUtility::CreateInstance())
	{
		return BasicUtility->Initialize(this);
	}
	
	return false;
}

void UITTGameInstanceBase::DestroyBasicUtility()
{
	if (TObjectPtr<UITTBasicUtility> BasicUtility = UITTBasicUtility::GetInstance())
	{
		BasicUtility->Finalize();
		UITTBasicUtility::DestroyInstance();
	}
}

bool UITTGameInstanceBase::CreateGameManagers()
{
	if (TObjectPtr<UITTSingletonManager> SingletonManager = UITTSingletonManager::CreateInstance())
	{
		SingletonManager->BuiltInInitializeSingletons();
		return true;
	}
	
	return false;
}

void UITTGameInstanceBase::InitializeGameManagers()
{
	if (TObjectPtr<UITTSingletonManager> SingletonManager = UITTSingletonManager::GetInstance())
	{
		SingletonManager->InitializeSingletons();
	}
}

void UITTGameInstanceBase::TickGameManagers(float DeltaSeconds)
{
	if (TObjectPtr<UITTSingletonManager> SingletonManager = UITTSingletonManager::GetInstance())
	{
		SingletonManager->TickSingletons(DeltaSeconds);
	}
}

void UITTGameInstanceBase::DestroyGameManagers()
{
	if (TObjectPtr<UITTSingletonManager> SingletonManager = UITTSingletonManager::GetInstance())
	{
		SingletonManager->FinalizeSingletons();
		UITTSingletonManager::DestroyInstance();
	}
}

bool UITTGameInstanceBase::RegisterTick()
{
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UITTGameInstanceBase::Tick));
	return true;
}

void UITTGameInstanceBase::UnregisterTick()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}
// ==================================== //