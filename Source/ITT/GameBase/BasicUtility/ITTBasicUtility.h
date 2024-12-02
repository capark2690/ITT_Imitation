// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Character/ITTDefine_Character.h"
#include "ITTBasicUtility.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTBasicUtility : public UObject
{
	GENERATED_BODY()

public:
	UITTBasicUtility();

	
	// ========== Instance ========== //
	static TObjectPtr<UITTBasicUtility> CreateInstance();
	static void DestroyInstance();
	
	static TObjectPtr<UITTBasicUtility> GetInstance() { return Instance; }

	bool Initialize(class UITTGameInstanceBase* _ITTGameInstance);
	void Finalize();
	// ============================== //
	
	
private:
	// ========== Composition ========== //
	void CreateCompositionObjects();
	void DestroyCompositionObjects();
	// ================================= //
	
	
public:
	// ========== BasicUtility ========== //
	static TWeakObjectPtr<class UITTGameInstanceBase> GetITTGameInstance();
	
	static class UWorld* GetITTWorld();
	
	static class AITTLevelScriptActor* GetITTLevelScriptActor();

	static class AITTPlayerControllerBase* GetFirstPlayerController();
	
	static class AITTPlayerController_InGame* GetPlayerController(EITTPlayerCharacterType PlayerCharacterType);
	
	static class AITTCharacter_Player* GetPlayerCharacter(EITTPlayerCharacterType PlayerCharacterType);
	// ================================== //

	
	// ========== GameConfig ========== //
	// -- Table -- //
	static const FString& GetTableListPath();
	// ================================ //

	
private:
	// ========== Instance ========== //
	static TObjectPtr<UITTBasicUtility> Instance;
	// ============================== //
	
	
	// ========== Composition ========== //
	TObjectPtr<class UITTGameConfig> ITTGameConfig;
	// ================================= //
	
	
	// ========== Utility ========== //
	TWeakObjectPtr<class UITTGameInstanceBase> ITTGameInstance;
	// ============================= //
};