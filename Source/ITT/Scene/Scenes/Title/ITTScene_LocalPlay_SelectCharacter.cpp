// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_LocalPlay_SelectCharacter.h"

#include "Engine/World.h"
#include "Engine/Level.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraActor.h"

#include "GameBase/BasicUtility/ITTBasicUtility.h"
#include "Level/Title/ITTLevelScriptActor_Title.h"

#include "GameBase/GameManager/GUI/ITTWidgetManager.h"
#include "GUI/Widget/Title/ITTWidget_CharacterSelect.h"
#include "Pawn/Title/ITTPawn_CharacterSelect.h"


UITTScene_LocalPlay_SelectCharacter::UITTScene_LocalPlay_SelectCharacter()
{
}


void UITTScene_LocalPlay_SelectCharacter::Initialize(EITTSceneType _SceneType)
{
	Super::Initialize(_SceneType);
	
	CreateWidget();
}

void UITTScene_LocalPlay_SelectCharacter::Finalize()
{
	Super::Finalize();
}

void UITTScene_LocalPlay_SelectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Widget ========== //
void UITTScene_LocalPlay_SelectCharacter::CreateWidget()
{
	if (UWorld* World = UITTBasicUtility::GetITTWorld())
	{
		if (WidgetMgr)
		{
			Widget_CharacterSelect = WidgetMgr->ITTCreateWidgetByTable<UITTWidget_CharacterSelect>(UITTWidget_CharacterSelect::GetClassWidgetKey(), World->GetFirstPlayerController());

			if (IsValid(Widget_CharacterSelect))
			{
				Widget_CharacterSelect->ChangeActivation(true);
			}
		}
	}
}
// ============================ //