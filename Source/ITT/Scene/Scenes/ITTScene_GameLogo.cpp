// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_GameLogo.h"

#include "GameBase/GameManager/GUI/ITTWidgetManager.h"
#include "GUI/Widget/Title/ITTWidget_GameLogo.h"


UITTScene_GameLogo::UITTScene_GameLogo()
{
}


void UITTScene_GameLogo::Initialize(EITTSceneType _SceneType)
{
	Super::Initialize(_SceneType);

	if (WidgetMgr)
	{
		TObjectPtr<UITTWidget> Widget = WidgetMgr->ITTCreateWidgetByTable(UITTWidget_GameLogo::GetClassWidgetKey());

		if (IsValid(Widget))
		{
			Widget->ChangeActivation(true);
		}
	}
}

void UITTScene_GameLogo::Finalize()
{
	if (WidgetMgr)
	{
		WidgetMgr->ITTDestroyWidget(UITTWidget_GameLogo::GetClassWidgetKey());
	}
	
	Super::Finalize();
}

void UITTScene_GameLogo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}