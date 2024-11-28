// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_ActorMarker.h"

#include "Components/Image.h"


UITTWidget_ActorMarker::UITTWidget_ActorMarker(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bRotation(false), DefaultRotationAngle(0.f)
{
}


void UITTWidget_ActorMarker::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UITTWidget_ActorMarker::NativeConstruct()
{
	Super::NativeConstruct();
}

void UITTWidget_ActorMarker::NativeDestruct()
{
	Super::NativeDestruct();
}

void UITTWidget_ActorMarker::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


// ========== UMG ========== //
void UITTWidget_ActorMarker::SetImageRotation(float Angle)
{
	if (bRotation)
	{
		IMG_Marker->SetRenderTransformAngle(DefaultRotationAngle + Angle);
	}
}
// ========================= //