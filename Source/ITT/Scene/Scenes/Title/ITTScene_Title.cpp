// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_Title.h"

#include "Engine/World.h"
#include "Engine/Level.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"

#include "GameBase/BasicUtility/ITTBasicUtility.h"
#include "Level/Title/ITTLevelScriptActor_Title.h"

#include "GameBase/GameManager/GUI/ITTWidgetManager.h"
#include "GUI/Widget/Title/ITTWidget_Title.h"


UITTScene_Title::UITTScene_Title()
{
}


void UITTScene_Title::Initialize(EITTSceneType _SceneType)
{
	Super::Initialize(_SceneType);

	CreateWidget();
	
	SetTargetCamera();
}

void UITTScene_Title::Finalize()
{
	DestroyWidget();
	
	Super::Finalize();
}

void UITTScene_Title::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Widget ========== //
void UITTScene_Title::CreateWidget()
{
	if (WidgetMgr)
	{
		TObjectPtr<UITTWidget> Widget = WidgetMgr->ITTCreateWidgetByTable(UITTWidget_Title::GetClassWidgetKey());

		if (IsValid(Widget))
		{
			Widget->ChangeActivation(true);
		}
	}
}

void UITTScene_Title::DestroyWidget()
{
	if (WidgetMgr)
	{
		WidgetMgr->ITTDestroyWidget(UITTWidget_Title::GetClassWidgetKey());
	}
}
// ============================ //


// ========== Camera ========== //
void UITTScene_Title::SetTargetCamera()
{
	if (UWorld* World = UITTBasicUtility::GetITTWorld())
	{
		AITTLevelScriptActor_Title* TitleLevelScript = Cast<AITTLevelScriptActor_Title>(World->GetLevel(0)->GetLevelScriptActor());
		if (TitleLevelScript)
		{
			World->GetFirstPlayerController()->SetViewTarget(TitleLevelScript->GetMainMenuCamera());
		}
	}
}
// ============================ //