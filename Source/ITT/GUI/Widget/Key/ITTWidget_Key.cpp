// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_Key.h"

#include "Components/Image.h"
#include "Data/Table/Tables/GUI/ITTTable_Key.h"
#include "GameBase/GameManager/Data/ITTTableManager.h"


UITTWidget_Key::UITTWidget_Key(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UITTWidget_Key::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetOwningPlayer() && GetOwningPlayer()->GetLocalPlayer())
	{
		UpdateKeyImage(GetOwningPlayer()->GetLocalPlayer()->GetControllerId());
	}
}


void UITTWidget_Key::UpdateKeyImage(int8 ControllerId)
{
	if (TableMgr)
	{
		if (UITTTable_Key* KeyTable = TableMgr->GetITTTable<UITTTable_Key>(UITTTable_Key::GetTableName()))
		{
			FSlateBrush SlateBrush_Bg;
			FSlateBrush SlateBrush_Key;

			// ToDo : Set Device for each controller
			FKey Key = ControllerId == 0 ? Key_Keyboard : Key_Gamepad;
			
			KeyTable->GetKeyBrush(Key, SlateBrush_Bg, SlateBrush_Key);

			IMG_Bg->SetBrush(SlateBrush_Bg);
			IMG_Key->SetBrush(SlateBrush_Key);
		}
	}
}
