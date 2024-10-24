﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_ProductionLogo.h"

#include "GameBase/GameManager/GUI/ITTWidgetManager.h"
#include "GUI/Widget/Title/ITTWidget_ProductionLogo.h"


UITTScene_ProductionLogo::UITTScene_ProductionLogo()
{
}


void UITTScene_ProductionLogo::Initialize(EITTSceneType _SceneType)
{
	Super::Initialize(_SceneType);

	CreateWidget();
}

void UITTScene_ProductionLogo::BeginPlay()
{
	Super::BeginPlay();
}

void UITTScene_ProductionLogo::Finalize()
{
	DestroyWidget();
	
	Super::Finalize();
}

void UITTScene_ProductionLogo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Widget ========== //
void UITTScene_ProductionLogo::CreateWidget()
{
	if (WidgetMgr)
	{
		TObjectPtr<UITTWidget> Widget = WidgetMgr->ITTCreateWidgetByTable(UITTWidget_ProductionLogo::GetClassWidgetKey());

		if (IsValid(Widget))
		{
			Widget->ChangeActivation(true);
		}
	}
}

void UITTScene_ProductionLogo::DestroyWidget()
{
	if (WidgetMgr)
	{
		WidgetMgr->ITTDestroyWidget(UITTWidget_ProductionLogo::GetClassWidgetKey());
	}
}
// ============================ //