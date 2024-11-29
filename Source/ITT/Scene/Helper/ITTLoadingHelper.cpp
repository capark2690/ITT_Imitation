// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTLoadingHelper.h"

#include "GameBase/GameManager/GUI/ITTWidgetManager.h"
#include "GUI/Widget/Loading/ITTWidget_Loading.h"


UITTLoadingHelper::UITTLoadingHelper()
	: bInitialized(false)
{
}


void UITTLoadingHelper::Initialize()
{
	if (!bInitialized)
	{
		{
			
		}
		
		bInitialized = true;
	}
}

void UITTLoadingHelper::Deinitialize()
{
	if (!bInitialized)
	{
		return;
	}
}


// ========== Loading ========== //
bool UITTLoadingHelper::StartLoading(EITTLoadingType LoadingType)
{
	if (!bInitialized)
	{
		return false;
	}

	if (LoadingType == EITTLoadingType::LoadingWidget)
	{
		if (!IsValid(LoadingWidget))
		{
			LoadingWidget = Cast<UITTWidget_Loading>(WidgetMgr->ITTCreateWidgetByTable(FName("WBP_Loading")));
		}

		LoadingWidget->OnStartLoading();
	}
	
	return true;
}

void UITTLoadingHelper::EndLoading(EITTLoadingType LoadingType)
{
	if (!bInitialized)
	{
		return;
	}
	
	if (LoadingType == EITTLoadingType::LoadingWidget)
	{
		if (IsValid(LoadingWidget))
		{
			LoadingWidget->OnEndLoading();
		}
	}
}
// ============================= //