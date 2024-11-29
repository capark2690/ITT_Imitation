// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_Loading.h"

#include "Animation/WidgetAnimation.h"


UITTWidget_Loading::UITTWidget_Loading(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), MinLoadingTime(2.f), LoadingTime(0.f), bEndLoading(false)
{
}


void UITTWidget_Loading::NativeConstruct()
{
	Super::NativeConstruct();
}

void UITTWidget_Loading::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	LoadingTime += InDeltaTime;

	if (LoadingTime >= MinLoadingTime)
	{
		if (bEndLoading == true)
		{
			bEndLoading = false;
			
			if (WAnim_Disappearance->IsValidLowLevel())
			{
				PlayAnimation(WAnim_Disappearance);
			}
		}
	}
}


// ========== Widget Animation ========== //
void UITTWidget_Loading::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	if (Animation == WAnim_Disappearance)
	{
		ChangeActivation(false);
	}
}

void UITTWidget_Loading::OnStartLoading()
{
	LoadingTime = 0.f;
	bEndLoading = false;
	
	ChangeActivation(true);
	
	if (WAnim_Appearance->IsValidLowLevel())
	{
		PlayAnimation(WAnim_Appearance);
	}
}

void UITTWidget_Loading::OnEndLoading()
{
	bEndLoading = true;
}
// ====================================== //