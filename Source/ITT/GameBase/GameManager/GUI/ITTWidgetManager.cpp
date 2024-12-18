﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidgetManager.h"

#include "GameBase/GameInstance/ITTGameInstanceBase.h"
#include "GameBase/BasicUtility/ITTBasicUtility.h"
#include "GameBase/GameManager/Data/ITTTableManager.h"
#include "Data/Table/Tables/GUI/ITTTable_WidgetList.h"
#include "GUI/Widget/ITTWidget.h"


UITTWidgetManager::UITTWidgetManager()
	: bBuiltInInitialized(false)
{
}


void UITTWidgetManager::BuiltInInitialize()
{
	bBuiltInInitialized = true;
}

void UITTWidgetManager::Finalize()
{
}


// ========== Create Widget ========== //
TObjectPtr<UITTWidget> UITTWidgetManager::ITTCreateWidgetByTable(const FName& WidgetName, APlayerController* WidgetOwner)
{
	if (!bBuiltInInitialized)
	{
		ITTLOG(Error, TEXT("[%s] WidgetManager is not initialized"), *ITTSTRING_FUNC);
		return nullptr;
	}
	
	UITTTableManager* TableManager = UITTTableManager::GetInstance();
	ITTCHECK(IsValid(TableManager));

	const FName& WidgetTableName = UITTTable_WidgetList::GetTableName();
	UITTTable_WidgetList* ITTTable_WidgetList = TableManager->GetITTTable<UITTTable_WidgetList>(WidgetTableName);
	ITTCHECK(IsValid(ITTTable_WidgetList));

	TSubclassOf<UITTWidget> WidgetClass;
	ITTTable_WidgetList->GetWidgetClass(WidgetName, WidgetClass);
	
	const TObjectPtr<UITTWidget>& Widget = ITTCreateWidget_Internal(WidgetClass, WidgetName, WidgetOwner, ITTTable_WidgetList->GetZOrder(WidgetName));
	if (Widget == nullptr)
	{
		ITTLOG(Error, TEXT("[%s] Create Widget Fail [WidgetName : %s]"), *ITTSTRING_FUNC, *WidgetName.ToString());
	}
	
	return Widget;
}

TObjectPtr<UITTWidget> UITTWidgetManager::ITTCreateWidgetByTable_WithOwnerWidget(const FName& WidgetName, UWidget* WidgetOwner)
{
	if (!bBuiltInInitialized)
	{
		ITTLOG(Error, TEXT("[%s] WidgetManager is not initialized"), *ITTSTRING_FUNC);
		return nullptr;
	}
	
	UITTTableManager* TableManager = UITTTableManager::GetInstance();
	ITTCHECK(IsValid(TableManager));

	const FName& WidgetTableName = UITTTable_WidgetList::GetTableName();
	UITTTable_WidgetList* ITTTable_WidgetList = TableManager->GetITTTable<UITTTable_WidgetList>(WidgetTableName);
	ITTCHECK(IsValid(ITTTable_WidgetList));

	TSubclassOf<UITTWidget> WidgetClass;
	ITTTable_WidgetList->GetWidgetClass(WidgetName, WidgetClass);
	
	const TObjectPtr<UITTWidget>& Widget = ITTCreateWidget_Internal_WithOwnerWidget(WidgetClass, WidgetName, WidgetOwner, ITTTable_WidgetList->GetZOrder(WidgetName));
	if (Widget == nullptr)
	{
		ITTLOG(Error, TEXT("[%s] Create Widget Fail [WidgetName : %s]"), *ITTSTRING_FUNC, *WidgetName.ToString());
	}
	
	return Widget;
}

TObjectPtr<UITTWidget> UITTWidgetManager::ITTCreateWidgetByClass(TSubclassOf<UITTWidget> WidgetClass, const FName& WidgetName,
                                                                 APlayerController* WidgetOwner, int32 ZOrder)
{
	if (!bBuiltInInitialized)
	{
		ITTLOG(Error, TEXT("[%s] WidgetManager is not initialized"), *ITTSTRING_FUNC);
		return nullptr;
	}
	
	const TObjectPtr<UITTWidget>& Widget = ITTCreateWidget_Internal(WidgetClass, WidgetName, WidgetOwner, ZOrder);
	if (Widget == nullptr)
	{
		ITTLOG(Error, TEXT("[%s] Create Widget Fail [WidgetName : %s]"), *ITTSTRING_FUNC, *WidgetName.ToString());
	}
	
	return Widget;
}

TObjectPtr<UITTWidget> UITTWidgetManager::ITTCreateWidgetByClass_WithOwnerWidget(TSubclassOf<UITTWidget> WidgetClass,
	const FName& WidgetName, UWidget* WidgetOwner, int32 ZOrder)
{
	if (!bBuiltInInitialized)
	{
		ITTLOG(Error, TEXT("[%s] WidgetManager is not initialized"), *ITTSTRING_FUNC);
		return nullptr;
	}
	
	const TObjectPtr<UITTWidget>& Widget = ITTCreateWidget_Internal_WithOwnerWidget(WidgetClass, WidgetName, WidgetOwner, ZOrder);
	if (Widget == nullptr)
	{
		ITTLOG(Error, TEXT("[%s] Create Widget Fail [WidgetName : %s]"), *ITTSTRING_FUNC, *WidgetName.ToString());
	}
	
	return Widget;
}

TObjectPtr<UITTWidget> UITTWidgetManager::ITTCreateWidget_Internal(TSubclassOf<class UITTWidget> WidgetClass,
	const FName& WidgetName, APlayerController* WidgetOwner, int32 ZOrder)
{
	if (WidgetClass == nullptr)
	{
		ITTLOG(Error, TEXT("[%s] WidgetClass on datatable is null [WidgetName : %s]"), *ITTSTRING_FUNC, *WidgetName.ToString());
		return nullptr;
	}
	
	TObjectPtr<UITTWidget> Widget;
	
	if (IsValid(WidgetOwner))
	{
		Widget = CreateWidget<UITTWidget>(WidgetOwner, WidgetClass);
	}
	else
	{
		Widget = CreateWidget<UITTWidget>(Cast<UGameInstance>(UITTBasicUtility::GetITTGameInstance()), WidgetClass);
	}

	if (Widget != nullptr)
	{
		Widget->BuiltInInitialize(ZOrder);
	}
	
	return Widget;
}

TObjectPtr<UITTWidget> UITTWidgetManager::ITTCreateWidget_Internal_WithOwnerWidget(TSubclassOf<UITTWidget> WidgetClass,
	const FName& WidgetName, UWidget* WidgetOwner, int32 ZOrder)
{
	if (WidgetClass == nullptr)
	{
		ITTLOG(Error, TEXT("[%s] WidgetClass on datatable is null [WidgetName : %s]"), *ITTSTRING_FUNC, *WidgetName.ToString());
		return nullptr;
	}
	
	TObjectPtr<UITTWidget> Widget;
	
	if (IsValid(WidgetOwner))
	{
		Widget = CreateWidget<UITTWidget>(WidgetOwner, WidgetClass);
	}
	else
	{
		Widget = CreateWidget<UITTWidget>(Cast<UGameInstance>(UITTBasicUtility::GetITTGameInstance()), WidgetClass);
	}

	if (Widget != nullptr)
	{
		Widget->BuiltInInitialize(ZOrder);
	}
	
	return Widget;
}
// =================================== //
