// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTButton.h"

#include "ITTTextBlock.h"


UITTButton::UITTButton()
{
}


TSharedRef<SWidget> UITTButton::RebuildWidget()
{
	OnChangeStringIndex();
	
	return Super::RebuildWidget();
}

void UITTButton::SynchronizeProperties()
{
	OnChangeStringIndex();
	
	Super::SynchronizeProperties();
}


void UITTButton::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	TXT_Button->SetStyle(GetCurrentTextStyleClass());
}


// ========== String Index ========== //
void UITTButton::SetStringIndex(int32 _StringIndex)
{
	StringIndex = _StringIndex;
}

void UITTButton::OnChangeStringIndex()
{
	if (TXT_Button)
	{
		TXT_Button->SetStringIndex(StringIndex);
	}
}
// ================================== //
