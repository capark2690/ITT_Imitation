// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_ProductionLogo.h"

#include "Animation/WidgetAnimation.h"
#include "GameBase/GameManager/GameBase/ITTSceneManager.h"


UITTWidget_ProductionLogo::UITTWidget_ProductionLogo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bWAnimFinished(false)
{
}


void UITTWidget_ProductionLogo::NativeConstruct()
{
	Super::NativeConstruct();

	StartLogoAnimation();
}

void UITTWidget_ProductionLogo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bWAnimFinished)
	{
		bWAnimFinished = false;
		ChangeScene();
	}
}


// ========== Widget Animation ========== //
void UITTWidget_ProductionLogo::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
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

void UITTWidget_ProductionLogo::StartLogoAnimation()
{
	if (WAnim_Appearance->IsValidLowLevel())
	{
		PlayAnimation(WAnim_Appearance);
	}
}
// ====================================== //


// ========== Finish ========== //
void UITTWidget_ProductionLogo::ChangeScene()
{
	if (SceneMgr)
	{
		SceneMgr->ChangeScene(EITTSceneType::GameLogo, EITTLoadingType::None, true);
	}
}
// ============================ //