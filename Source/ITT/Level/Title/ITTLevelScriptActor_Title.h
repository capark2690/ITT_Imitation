// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "ITTLevelScriptActor_Title.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API AITTLevelScriptActor_Title : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AITTLevelScriptActor_Title();

	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	

	// ==================== Getter ==================== //
	// ========== Camera ========== //
	// -- MainMenu -- //
	class ACameraActor* GetMainMenuCamera() const { return MainMenuCamera; }


	// -- Character Select -- //
	class ACameraActor* GetCharacterSelectCamera() const { return CharacterSelectCamera; }
	// ============================ //
	// ================================================ //

	
protected:
	// ========== Camera ========== //
	// -- MainMenu -- //
	UPROPERTY(Category=ITT, EditAnywhere)
	TObjectPtr<class ACameraActor> MainMenuCamera;


	// -- Character Select -- //
	UPROPERTY(Category=ITT, EditAnywhere)
	TObjectPtr<class ACameraActor> CharacterSelectCamera;
	// ============================ //
};
