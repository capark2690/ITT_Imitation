// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_CharacterSelect.h"

#include "EnhancedInputComponent.h"

#include "GameBase/GameManager/GameBase/ITTGameProcessManager.h"
#include "GameBase/GameManager/GameBase/ITTSceneManager.h"

#include "Button/ITTWidget_Button_CharacterSelect.h"
#include "GUI/UMGComponent/Additive/Button/ITTButton_WithKey.h"

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"


UITTWidget_CharacterSelect::UITTWidget_CharacterSelect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), NextSceneType(EITTSceneType::Title_MainMenu), bConfirm_Player1(false), bConfirm_Player2(false)
{
}


void UITTWidget_CharacterSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BindButtons();
	BindInputAction();
}

void UITTWidget_CharacterSelect::NativeConstruct()
{
	Super::NativeConstruct();
	
	UpdateDesign_BTN();
}

void UITTWidget_CharacterSelect::NativeDestruct()
{
	ClearInputActionBindings();
	
	Super::NativeDestruct();
}

void UITTWidget_CharacterSelect::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


// ========== Close ========== //
void UITTWidget_CharacterSelect::PrepareToFinish()
{
	PlayDisappearanceWidgetAnimation();
}

void UITTWidget_CharacterSelect::Finish()
{
	Super::Finish();

	if (SceneMgr)
	{
		if (NextSceneType == EITTSceneType::Ch1_Awakening)
		{
			SceneMgr->ChangeScene(NextSceneType, EITTLoadingType::LoadingWidget, true);
		}
		else
		{
			SceneMgr->ChangeScene(NextSceneType, EITTLoadingType::None, true);
		}
	}
}
// =========================== //


// ========== Button ========== //
void UITTWidget_CharacterSelect::BindButtons()
{
	BTN_Back->OnClicked().AddUObject(this, &UITTWidget_CharacterSelect::OnClickButton_Back);
}

void UITTWidget_CharacterSelect::OnClickButton_Back()
{
	InputBack();
}
// ============================ //


// ========== Input Action ========== //
void UITTWidget_CharacterSelect::BindInputAction()
{
	if (APlayerController* Player1 = UGameplayStatics::GetPlayerControllerFromID(this, 0))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player1->InputComponent))
		{
			EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputConfirm_Player1);
	
			EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputRight_Player1);
		
			EnhancedInputComponent->BindAction(LeftAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputLeft_Player1);

			EnhancedInputComponent->BindAction(BackAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputBack);
		}
	}

	if (APlayerController* Player2 = UGameplayStatics::GetPlayerControllerFromID(this, 1))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player2->InputComponent))
		{
			EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputConfirm_Player2);
	
			EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputRight_Player2);
		
			EnhancedInputComponent->BindAction(LeftAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputLeft_Player2);

			EnhancedInputComponent->BindAction(BackAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputBack);
		}
	}
}

void UITTWidget_CharacterSelect::ClearInputActionBindings()
{
	if (APlayerController* Player1 = UGameplayStatics::GetPlayerControllerFromID(this, 0))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player1->InputComponent))
		{
			EnhancedInputComponent->ClearActionBindings();
		}
	}

	if (APlayerController* Player2 = UGameplayStatics::GetPlayerControllerFromID(this, 1))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player2->InputComponent))
		{
			EnhancedInputComponent->ClearActionBindings();
		}
	}
}
// ================================== //


// ========== Input ========== //
// -- Player1 -- //
void UITTWidget_CharacterSelect::InputConfirm_Player1()
{
	if (SelectedPlayerCharacterType1 != EITTPlayerCharacterType::None)
	{
		bConfirm_Player1 = true;
		CheckConfirm();
	}

	UpdateDesign_BTN();
}

void UITTWidget_CharacterSelect::InputRight_Player1()
{
	if (SelectedPlayerCharacterType1 == EITTPlayerCharacterType::None && SelectedPlayerCharacterType2 != EITTPlayerCharacterType::Cody)
	{
		SelectedPlayerCharacterType1 = EITTPlayerCharacterType::Cody;
	}
	
	if (SelectedPlayerCharacterType1 == EITTPlayerCharacterType::May)
	{
		SelectedPlayerCharacterType1 = EITTPlayerCharacterType::None;
		
		bConfirm_Player1 = false;
	}
	
	OnChangeCharacterSelectState();
}

void UITTWidget_CharacterSelect::InputLeft_Player1()
{
	if (SelectedPlayerCharacterType1 == EITTPlayerCharacterType::None && SelectedPlayerCharacterType2 != EITTPlayerCharacterType::May)
	{
		SelectedPlayerCharacterType1 = EITTPlayerCharacterType::May;
	}
	
	if (SelectedPlayerCharacterType1 == EITTPlayerCharacterType::Cody)
	{
		SelectedPlayerCharacterType1 = EITTPlayerCharacterType::None;
		
		bConfirm_Player1 = false;
	}

	OnChangeCharacterSelectState();
}


// -- Player2 -- //
void UITTWidget_CharacterSelect::InputConfirm_Player2()
{
	if (SelectedPlayerCharacterType2 != EITTPlayerCharacterType::None)
	{
		bConfirm_Player2 = true;
		CheckConfirm();
	}
	
	UpdateDesign_BTN();
}

void UITTWidget_CharacterSelect::InputRight_Player2()
{
	if (SelectedPlayerCharacterType2 == EITTPlayerCharacterType::None && SelectedPlayerCharacterType1 != EITTPlayerCharacterType::Cody)
	{
		SelectedPlayerCharacterType2 = EITTPlayerCharacterType::Cody;
	}
	
	if (SelectedPlayerCharacterType2 == EITTPlayerCharacterType::May)
	{
		SelectedPlayerCharacterType2 = EITTPlayerCharacterType::None;
		
		bConfirm_Player2 = false;
	}

	OnChangeCharacterSelectState();
}

void UITTWidget_CharacterSelect::InputLeft_Player2()
{
	if (SelectedPlayerCharacterType2 == EITTPlayerCharacterType::None && SelectedPlayerCharacterType1 != EITTPlayerCharacterType::May)
	{
		SelectedPlayerCharacterType2 = EITTPlayerCharacterType::May;
	}
	
	if (SelectedPlayerCharacterType2 == EITTPlayerCharacterType::Cody)
	{
		SelectedPlayerCharacterType2 = EITTPlayerCharacterType::None;
		
		bConfirm_Player2 = false;
	}

	OnChangeCharacterSelectState();
}


// -- Both -- //
void UITTWidget_CharacterSelect::InputBack()
{
	NextSceneType = EITTSceneType::Title_MainMenu;
	ITTCloseWidget(true);
}
// =========================== //


// ========== Progress ========== //
void UITTWidget_CharacterSelect::CheckConfirm()
{
	if (bConfirm_Player1  && bConfirm_Player2)
	{
		if (GameProcessMgr)
		{
			GameProcessMgr->ResetControllerIdToCharacter();

			GameProcessMgr->AddControllerIdToCharacterType(0, SelectedPlayerCharacterType1);
			GameProcessMgr->AddControllerIdToCharacterType(1, SelectedPlayerCharacterType2);
		}

		NextSceneType = EITTSceneType::Ch1_Awakening;
		ITTCloseWidget(false);
	}
}
// ============================== //


// ========== Design ========== //
void UITTWidget_CharacterSelect::UpdateDesign_BTN()
{
	ESlateVisibility Visibility_SelectBTN_Player1 = ESlateVisibility::Hidden;
	ESlateVisibility Visibility_SelectBTN_Player2 = ESlateVisibility::Hidden;
	ESlateVisibility Visibility_ConfirmBTN_Right = ESlateVisibility::Hidden;
	ESlateVisibility Visibility_ConfirmBTN_Left = ESlateVisibility::Hidden;
	
	bool bConfirm_ConfirmBTN_Right = false;
	bool bConfirm_ConfirmBTN_Left = false;
	
	switch (SelectedPlayerCharacterType1)
	{
	case EITTPlayerCharacterType::None:
		{
			Visibility_SelectBTN_Player1 = ESlateVisibility::SelfHitTestInvisible;
			break;
		}
		
	case EITTPlayerCharacterType::Cody:
		{
			Visibility_ConfirmBTN_Right = ESlateVisibility::SelfHitTestInvisible;
			WBP_ConfirmBTN_Right->SetControllerId(0);

			bConfirm_ConfirmBTN_Right = bConfirm_Player1;
			break;
		}

	case EITTPlayerCharacterType::May:
		{
			Visibility_ConfirmBTN_Left = ESlateVisibility::SelfHitTestInvisible;
			WBP_ConfirmBTN_Left->SetControllerId(0);

			bConfirm_ConfirmBTN_Left = bConfirm_Player1;
			break;
		}
	}
	
	switch (SelectedPlayerCharacterType2)
	{
	case EITTPlayerCharacterType::None:
		{
			Visibility_SelectBTN_Player2 = ESlateVisibility::SelfHitTestInvisible;
			break;
		}
		
	case EITTPlayerCharacterType::Cody:
		{
			Visibility_ConfirmBTN_Right = ESlateVisibility::SelfHitTestInvisible;
			WBP_ConfirmBTN_Right->SetControllerId(1);
			
			bConfirm_ConfirmBTN_Right = bConfirm_Player2;
			break;
		}

	case EITTPlayerCharacterType::May:
		{
			Visibility_ConfirmBTN_Left = ESlateVisibility::SelfHitTestInvisible;
			WBP_ConfirmBTN_Left->SetControllerId(1);

			bConfirm_ConfirmBTN_Left = bConfirm_Player2;
			break;
		}
	}

	WBP_SelectBTN_Player1->SetVisibility(Visibility_SelectBTN_Player1);
	WBP_SelectBTN_Player2->SetVisibility(Visibility_SelectBTN_Player2);
	WBP_ConfirmBTN_Right->SetVisibility(Visibility_ConfirmBTN_Right);
	WBP_ConfirmBTN_Left->SetVisibility(Visibility_ConfirmBTN_Left);
	
	WBP_ConfirmBTN_Right->SetConfirmWidgetSwitcher(bConfirm_ConfirmBTN_Right);
	WBP_ConfirmBTN_Left->SetConfirmWidgetSwitcher(bConfirm_ConfirmBTN_Left);
}
// ============================ //


// ========== Widget Animation ========== //
void UITTWidget_CharacterSelect::PlayDisappearanceWidgetAnimation()
{
	PlayAnimation(WAnim_Disappearance);
}

void UITTWidget_CharacterSelect::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	if (Animation == WAnim_Disappearance)
	{
		Finish();
	}
}
// ====================================== //


// ========== Character Select State ========== //
void UITTWidget_CharacterSelect::OnChangeCharacterSelectState()
{
	bool bDelegateBound = OnChangeCharacterSelectStateDelegate.ExecuteIfBound(SelectedPlayerCharacterType1, SelectedPlayerCharacterType2);
	UpdateDesign_BTN();
}

void UITTWidget_CharacterSelect::GetCharacterSelectState(EITTPlayerCharacterType& OutSelectPlayerCharacterType1,
	EITTPlayerCharacterType& OutSelectPlayerCharacterType2) const
{
	OutSelectPlayerCharacterType1 = SelectedPlayerCharacterType1;
	OutSelectPlayerCharacterType2 = SelectedPlayerCharacterType2;
}
// ============================================ //