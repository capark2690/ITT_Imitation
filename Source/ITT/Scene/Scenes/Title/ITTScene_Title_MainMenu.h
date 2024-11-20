// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ITTSceneBase.h"
#include "ITTScene_Title_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTScene_Title_MainMenu : public UITTSceneBase
{
	GENERATED_BODY()

public:
	UITTScene_Title_MainMenu();

	
	virtual void Initialize(EITTSceneType _SceneType, struct FITTTableRow_Scene* _SceneRow) override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;


private:
	// ========== Widget ========== //
	void CreateWidget();
	void DestroyWidget();
	// ============================ //
};