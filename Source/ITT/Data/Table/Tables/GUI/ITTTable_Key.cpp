// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTTable_Key.h"


UITTTable_Key::UITTTable_Key()
{
}


void UITTTable_Key::GetKeyBrush(const FKey& InKey, FSlateBrush& OutSlateBrush_Bg, FSlateBrush& OutSlateBrush_Key, FText& OutText_Key) const
{
	FName RowName = InKey.GetFName();
	FITTTableRow_Key* Row = GetDataTable()->FindRow<FITTTableRow_Key>(RowName, ITTTEXT_FUNC);
	if (Row)
	{
		OutSlateBrush_Bg = Row->SlateBrush_Bg;
		OutSlateBrush_Key = Row->SlateBrush_Key;
		OutText_Key = Row->Text_Key;
	}
}
