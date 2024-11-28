// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_HUD_ActorMarker.h"

#include "SceneView.h"
#include "Camera/CameraComponent.h"
#include "Engine/GameViewportClient.h"

#include "GameBase/GameManager/GUI/ITTWidgetManager.h"
#include "GameBase/GameManager/Object/ITTActorManager.h"
#include "Player/PlayerController/ITTPlayerController_InGame.h"

#include "Component/Actor/Widget/ITTWidgetMarkerComponent.h"
#include "GUI/Widget/ActorMarker/ITTWidget_ActorMarker.h"


UITTWidget_HUD_ActorMarker::UITTWidget_HUD_ActorMarker(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UITTWidget_HUD_ActorMarker::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BindToActorManager();
}

void UITTWidget_HUD_ActorMarker::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateMakerList();
}

void UITTWidget_HUD_ActorMarker::NativeDestruct()
{
	UnbindToActorManager();
	
	Super::NativeDestruct();
}

void UITTWidget_HUD_ActorMarker::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	UpdateMakerLocations();
}

void UITTWidget_HUD_ActorMarker::BindToActorManager()
{
	if (ActorMgr)
	{
		ActorMgr->OnUpdateActorMarker.BindUObject(this, &UITTWidget_HUD_ActorMarker::UpdateMakerList);
	}
}

void UITTWidget_HUD_ActorMarker::UnbindToActorManager()
{
	if (ActorMgr)
	{
		ActorMgr->OnUpdateActorMarker.Unbind();
	}
}

void UITTWidget_HUD_ActorMarker::UpdateMakerList()
{
	if (ActorMgr && WidgetMgr)
	{
		TArray<TWeakObjectPtr<UITTWidgetMarkerComponent>> MarkerComponents = ActorMgr->GetMarkerComponents();
		
		// 기존 MarkerWidget 중 MarkerComponents에 없는 것 삭제
		for (auto Iter = MarkerWidgetToMarkerComponents.CreateIterator(); Iter; ++Iter)
		{
			if (MarkerComponents.Contains(Iter.Value()))
			{
				MarkerComponents.RemoveSingle(Iter.Value());
			}

			else
			{
				if (IsValid(Iter.Key()))
				{
					Iter.Key()->ITTCloseWidget(true);
				}

				Iter.RemoveCurrent();
			}
		}
		
		for (TWeakObjectPtr<UITTWidgetMarkerComponent>& MarkerComponent : MarkerComponents)
		{
			UITTWidget_ActorMarker* NewMarker = WidgetMgr->ITTCreateWidgetByTable_WithOwnerWidget<UITTWidget_ActorMarker>(MarkerComponent->GetMarkerWidgetKey(), this);
			NewMarker->ChangeActivation(true);
			
			MarkerWidgetToMarkerComponents.Emplace(NewMarker, MarkerComponent);
		}
	}
}

void UITTWidget_HUD_ActorMarker::UpdateMakerLocations()
{
	if (AITTPlayerController_InGame* PlayerController = Cast<AITTPlayerController_InGame>(GetOwningPlayer()))
	{
		for (auto Iter = MarkerWidgetToMarkerComponents.CreateIterator(); Iter; ++Iter)
		{
			if (!IsOwnerPlayerTypeMakerable(Iter.Value()))
			{
				Iter.Key()->SetVisibility(ESlateVisibility::Collapsed);
				return;
			}

			FSceneViewProjectionData ProjectionData;
			FVector ScreenLocation;
			
			FVector TargetActorLocation = Iter.Value()->GetComponentLocation();

			bool bIsInsideView = GetTargetScreenLocation(TargetActorLocation, ScreenLocation, ProjectionData);

			//ITTLOG(Warning, TEXT("[%s] [WidgetName : %s] ScreenLocation_Test : %f, %f, %f"), *ITTSTRING_FUNC, *Iter.Key()->GetName(),
			//ScreenLocation.X, ScreenLocation.Y, ScreenLocation.Z);
			
			if (bIsInsideView)
			{
				Iter.Key()->SetPositionInViewport(FVector2d(ScreenLocation.X, ScreenLocation.Y));
				
				bool bOutside_Left = ScreenLocation.X < 0.f;
				bool bOutside_Right = ScreenLocation.X > ProjectionData.GetViewRect().Width();
				bool bOutside_Top = ScreenLocation.Y < 0.f;
				bool bOutside_Bottom = ScreenLocation.Y > ProjectionData.GetViewRect().Height();

				// SetImageRotation
				float RotationAngle = 0.f;
				
				float OutsideValue_X = 0.f;
				float OutsideValue_Y = 0.f;
				
				if (bOutside_Left)
				{
					OutsideValue_X = -ScreenLocation.X;
				}
				else if (bOutside_Right)
				{
					OutsideValue_X = ProjectionData.GetViewRect().Width() - ScreenLocation.X;
				}
				
				if (bOutside_Top)
				{
					OutsideValue_Y = -ScreenLocation.Y;
				}
				else if (bOutside_Bottom)
				{
					OutsideValue_Y = ProjectionData.GetViewRect().Height() - ScreenLocation.Y;
				}


				if (bOutside_Left)
				{
					if (bOutside_Top)
					{
						RotationAngle = OutsideValue_X >= OutsideValue_Y ? 90.f : 180.f;
					}
					else if (bOutside_Bottom)
					{
						RotationAngle = OutsideValue_X >= OutsideValue_Y ? 90.f : 0.f;
					}
					else
					{
						RotationAngle = 90.f;
					}
				}
				else if (bOutside_Right)
				{
					if (bOutside_Top)
					{
						RotationAngle = OutsideValue_X >= OutsideValue_Y ? -90.f : 180.f;
					}
					else if (bOutside_Bottom)
					{
						RotationAngle = OutsideValue_X >= OutsideValue_Y ? -90.f : 0.f;
					}
					else
					{
						RotationAngle = -90.f;
					}
				}
				else
				{
					if (bOutside_Top)
					{
						RotationAngle = 180.f;
					}
					else if (bOutside_Bottom)
					{
						RotationAngle = 0.f;
					}
				}

				Iter.Key()->SetImageRotation(RotationAngle);
				
				// SetPositionInViewport
				FVector2d WidgetPosition = FVector2d(ScreenLocation.X, ScreenLocation.Y);
				
				if (bOutside_Left)
				{
					WidgetPosition.X = 0.f;
				}
				else if (bOutside_Right)
				{
    				WidgetPosition.X = ProjectionData.GetViewRect().Width() - Iter.Key()->GetCachedGeometry().GetDrawSize().X;
				}

				if (bOutside_Top)
				{
					WidgetPosition.Y = 0.f;
				}
				else if (bOutside_Bottom)
				{
					WidgetPosition.Y = ProjectionData.GetViewRect().Height() - Iter.Key()->GetCachedGeometry().GetDrawSize().Y;
				}

				Iter.Key()->SetPositionInViewport(WidgetPosition);
			}
		}
	}
}

bool UITTWidget_HUD_ActorMarker::GetTargetScreenLocation(const FVector& InWorldLocation, FVector& OutScreenLocation, FSceneViewProjectionData& ProjectionData)
{
	bool bIsInsideView = false;
	
	if (AITTPlayerController_InGame* PlayerController = Cast<AITTPlayerController_InGame>(GetOwningPlayer()))
	{
		ULocalPlayer const* const LP = PlayerController->GetLocalPlayer();
		if (LP && LP->ViewportClient)
		{
			if (LP->GetProjectionData(LP->ViewportClient->Viewport, ProjectionData))
			{
				FVector2D ScreenPosition2D;
				FMatrix const ViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();

				bIsInsideView = FSceneView::ProjectWorldToScreen(InWorldLocation, ProjectionData.GetConstrainedViewRect(), ViewProjectionMatrix, ScreenPosition2D, true);
				
				ScreenPosition2D -= FVector2D(ProjectionData.GetConstrainedViewRect().Min);

				OutScreenLocation = FVector(ScreenPosition2D.X, ScreenPosition2D.Y, FVector::Dist(ProjectionData.ViewOrigin, InWorldLocation));
			}
		}
	}
	
	return bIsInsideView;
}

bool UITTWidget_HUD_ActorMarker::IsOwnerPlayerTypeMakerable(TWeakObjectPtr<class UITTWidgetMarkerComponent> WidgetMarkerComponent) const
{
	if (AITTPlayerController_InGame* PlayerController = Cast<AITTPlayerController_InGame>(GetOwningPlayer()))
	{
		if (PlayerController->GetPlayerCharacterType() == EITTPlayerCharacterType::Cody && !WidgetMarkerComponent->GetMarkOnCodyScreen())
		{
			return false;
		}

		if (PlayerController->GetPlayerCharacterType() == EITTPlayerCharacterType::May && !WidgetMarkerComponent->GetMarkOnMayScreen())
		{
			return false;
		}
	}

	return true;
}
