// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTScene_LocalPlay_SelectCharacter.h"

#include "Actor/ITTActor_LevelSpecific.h"
#include "Animation/Animation/Actor/Title/ITTAnimInstance_CharacterSelect.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"

#include "GameBase/BasicUtility/ITTBasicUtility.h"
#include "Level/Title/ITTLevelScriptActor_Title.h"

#include "GameBase/GameManager/GUI/ITTWidgetManager.h"
#include "GUI/Widget/Title/ITTWidget_CharacterSelect.h"


UITTScene_LocalPlay_SelectCharacter::UITTScene_LocalPlay_SelectCharacter()
{
}


void UITTScene_LocalPlay_SelectCharacter::Initialize(EITTSceneType _SceneType, FITTTableRow_Scene* _SceneRow)
{
	Super::Initialize(_SceneType, _SceneRow);
	
	CreateWidget();
}

void UITTScene_LocalPlay_SelectCharacter::Finalize()
{
	Super::Finalize();
}

void UITTScene_LocalPlay_SelectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ========== Widget ========== //
void UITTScene_LocalPlay_SelectCharacter::CreateWidget()
{
	if (UWorld* World = UITTBasicUtility::GetITTWorld())
	{
		if (WidgetMgr)
		{
			Widget_CharacterSelect = WidgetMgr->ITTCreateWidgetByTable<UITTWidget_CharacterSelect>(UITTWidget_CharacterSelect::GetClassWidgetKey(), World->GetFirstPlayerController());

			if (IsValid(Widget_CharacterSelect))
			{
				Widget_CharacterSelect->ChangeActivation(true);
				BindToCharacterSelectWidget();
			}
		}
	}
}
// ============================ //


// ========== Character Select State ========== //
void UITTScene_LocalPlay_SelectCharacter::BindToCharacterSelectWidget()
{
	if (IsValid(Widget_CharacterSelect))
	{
		Widget_CharacterSelect->OnChangeCharacterSelectStateDelegate.BindUObject(this,
			&UITTScene_LocalPlay_SelectCharacter::OnChangeCharacterSelectState);
	}
}

void UITTScene_LocalPlay_SelectCharacter::OnChangeCharacterSelectState(
	EITTPlayerCharacterType SelectedPlayerCharacterType1, EITTPlayerCharacterType SelectedPlayerCharacterType2)
{
	if (AITTLevelScriptActor* LevelScriptActor = UITTBasicUtility::GetITTLevelScriptActor())
	{
		if (AITTActor_LevelSpecific* CharacterSelectActor = LevelScriptActor->GetLevelSpecificActor<AITTActor_LevelSpecific>(FName(ActorKey_CharacterSelect)))
		{
			TArray<UActorComponent*> Components = CharacterSelectActor->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), FName(ComponentTag_CharacterSelectMesh));

			for (UActorComponent* Component : Components)
			{
				if (USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(Component))
				{
					if (UITTAnimInstance_CharacterSelect* AnimInstance = Cast<UITTAnimInstance_CharacterSelect>(MeshComponent->GetAnimInstance()))
					{
						AnimInstance->UpdateCharacterSelectState(SelectedPlayerCharacterType1, SelectedPlayerCharacterType2);
					}
				}
			}
		}
	}
}

void UITTScene_LocalPlay_SelectCharacter::GetCharacterSelectState(EITTPlayerCharacterType& OutSelectCharacter_Player1,
                                                                  EITTPlayerCharacterType& OutSelectCharacter_Player2) const
{
	if (IsValid(Widget_CharacterSelect))
	{
		Widget_CharacterSelect->GetCharacterSelectState(OutSelectCharacter_Player1, OutSelectCharacter_Player2);
	}
}
// ============================================ //