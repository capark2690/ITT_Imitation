// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTSingletonManager.h"

#include "ITTSingleton.h"

#include "GameBase/GameManager/Data/ITTTableManager.h"
#include "GameBase/GameManager/GUI/ITTWidgetManager.h"
#include "GameBase/GameManager/Camera/ITTCameraManager.h"
#include "GameBase/GameManager/GameBase/ITTLevelManager.h"
#include "GameBase/GameManager/GameBase/ITTSceneManager.h"
#include "GameBase/GameManager/GameBase/ITTGameProcessManager.h"
#include "GameBase/GameManager/Object/ITTActorManager.h"


TObjectPtr<UITTSingletonManager> UITTSingletonManager::Instance = nullptr;


UITTSingletonManager::UITTSingletonManager()
	: bBuiltInInitialized(false), bInitialized(false)
{
}


// ========== Instance ========== //
TObjectPtr<UITTSingletonManager> UITTSingletonManager::CreateInstance()
{
	Instance = ITTNewObject<UITTSingletonManager>();
	if (Instance)
	{
		Instance->AddToRoot();
		Instance->RegisterSingletons();
		Instance->RegisterSingletonsForTick();
	}
	
	return Instance;
}

void UITTSingletonManager::DestroyInstance()
{
	if (IsValid(Instance))
	{
		Instance->UnregisterSingletons();
		Instance->RemoveFromRoot();
		ITTDeleteObject(Instance);
	}
}
// ============================== //


// ========== Singletons ========== //
void UITTSingletonManager::BuiltInInitializeSingletons()
{
	if (!bBuiltInInitialized)
	{
		for (IITTSingleton* Singleton : Singletons)
		{
			Singleton->BuiltInInitialize();
		}

		bBuiltInInitialized = true;
	}
}

void UITTSingletonManager::InitializeSingletons()
{
	if (!bInitialized)
	{
		for (IITTSingleton* Singleton : Singletons)
		{
			Singleton->Initialize();
		}

		for (IITTSingleton* Singleton : Singletons)
		{
			Singleton->PostInitialize();
		}
		
		bInitialized = true;
	}
}

void UITTSingletonManager::FinalizeSingletons()
{
	for (IITTSingleton* Singleton : Singletons)
	{
		if (bInitialized)
		{
			Singleton->PreFinalize();
			Singleton->Finalize();
		}
	}

	bInitialized = false;
	
	for (IITTSingleton* Singleton : Singletons)
	{
		if (bBuiltInInitialized)
		{
			Singleton->BuiltInFinalize();
		}
	}
	
	bBuiltInInitialized = false;
}

void UITTSingletonManager::TickSingletons(float DeltaTime)
{
	if (bInitialized)
	{
		for (IITTSingleton* Singleton : SingletonsForTick)
		{
			Singleton->Tick(DeltaTime);
		}
	}
}


void UITTSingletonManager::RegisterSingletons()
{
	Singletons.Reset();
	
	// Singletons.Emplace([Class]::CreateInstance());
	Singletons.Emplace(UITTTableManager::CreateInstance());
	Singletons.Emplace(UITTWidgetManager::CreateInstance());
	Singletons.Emplace(UITTCameraManager::CreateInstance());
	Singletons.Emplace(UITTLevelManager::CreateInstance());
	Singletons.Emplace(UITTSceneManager::CreateInstance());
	Singletons.Emplace(UITTGameProcessManager::CreateInstance());
	Singletons.Emplace(UITTActorManager::CreateInstance());
}

void UITTSingletonManager::RegisterSingletonsForTick()
{
	SingletonsForTick.Reset();
	
	// SingletonsForTick.Emplace([Class]::CreateInstance());
	SingletonsForTick.Emplace(UITTCameraManager::CreateInstance());
	SingletonsForTick.Emplace(UITTSceneManager::CreateInstance());
}

void UITTSingletonManager::UnregisterSingletons()
{
	Singletons.Reset();
	SingletonsForTick.Reset();
	
	// [Class]::DestroyInstance();
	UITTActorManager::DestroyInstance();
	UITTGameProcessManager::DestroyInstance();
	UITTSceneManager::DestroyInstance();
	UITTLevelManager::DestroyInstance();
	UITTCameraManager::DestroyInstance();
	UITTWidgetManager::DestroyInstance();
	UITTTableManager::DestroyInstance();
}
// ================================ //