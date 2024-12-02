// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_Title_MainMenu.h"

#include "Engine/World.h"

#include "GameBase/GameManager/GUI/ITTWidgetManager.h"
#include "GUI/Widget/Title/ITTWidget_Title.h"


UITTScene_Title_MainMenu::UITTScene_Title_MainMenu()
{
}


void UITTScene_Title_MainMenu::Initialize(EITTSceneType _SceneType, FITTTableRow_Scene* _SceneRow)
{
	Super::Initialize(_SceneType, _SceneRow);

	CreateWidget();
}

void UITTScene_Title_MainMenu::Finalize()
{
	DestroyWidget();
	
	Super::Finalize();
}

void UITTScene_Title_MainMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Widget ========== //
void UITTScene_Title_MainMenu::CreateWidget()
{
	if (WidgetMgr)
	{
		Widget = WidgetMgr->ITTCreateWidgetByTable(UITTWidget_Title::GetClassWidgetKey());

		if (IsValid(Widget))
		{
			Widget->ChangeActivation(true);
		}
	}
}

void UITTScene_Title_MainMenu::DestroyWidget()
{
	if (IsValid(Widget))
	{
		Widget->ITTCloseWidget(true);
	}
}
// ============================ //