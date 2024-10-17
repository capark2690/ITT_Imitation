// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_GameLogo.h"

#include "Animation/WidgetAnimation.h"
#include "GameBase/GameManager/GameBase/ITTSceneManager.h"


UITTWidget_GameLogo::UITTWidget_GameLogo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bWAnimFinished(false)
{
}


void UITTWidget_GameLogo::NativeConstruct()
{
	Super::NativeConstruct();

	StartLogoAnimation();
}

void UITTWidget_GameLogo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bWAnimFinished)
	{
		bWAnimFinished = false;
		ChangeScene();
	}
}


// ========== Widget Animation ========== //
void UITTWidget_GameLogo::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
	
	if (Animation == WAnim_Appearance)
	{
		if (WAnim_Disappearance->IsValidLowLevel())
		{
			PlayAnimation(WAnim_Disappearance);
			return;
		}
	}
	
	bWAnimFinished = true;
}

void UITTWidget_GameLogo::StartLogoAnimation()
{
	if (WAnim_Appearance->IsValidLowLevel())
	{
		PlayAnimation(WAnim_Appearance);
	}
}
// ====================================== //


// ========== Finish ========== //
void UITTWidget_GameLogo::ChangeScene()
{
	if (SceneMgr)
	{
		SceneMgr->ChangeScene(EITTSceneType::Title, EITTLoadingType::None, true);
	}
}
// ============================ //