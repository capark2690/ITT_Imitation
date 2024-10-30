// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_CharacterSelect.h"

#include "EnhancedInputComponent.h"

#include "GameBase/GameManager/GameBase/ITTGameProcessManager.h"
#include "GameBase/GameManager/GameBase/ITTSceneManager.h"

#include "Button/ITTWidget_Button_CharacterSelect.h"

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"


UITTWidget_CharacterSelect::UITTWidget_CharacterSelect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bConfirm_Player1(false), bConfirm_Player2(false)
{
}


void UITTWidget_CharacterSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

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
		SceneMgr->ChangeScene(EITTSceneType::Ch1_Start, EITTLoadingType::None, true);
	}
}
// =========================== //


// ========== Input Action ========== //
void UITTWidget_CharacterSelect::BindInputAction()
{
	if (APlayerController* Player1 = UGameplayStatics::GetPlayerControllerFromID(this, 0))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player1->InputComponent))
		{
			EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputConfirm_Player1);
	
			EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputRight_Player1);
		
			EnhancedInputComponent->BindAction(LeftAction, ETriggerEvent::Triggered, this, &UITTWidget_CharacterSelect::InputLeft_Player1);
		}
	}

	if (APlayerController* Player2 = UGameplayStatics::GetPlayerControllerFromID(this, 1))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player2->InputComponent))
		{
			EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputConfirm_Player2);
	
			EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputRight_Player2);
		
			EnhancedInputComponent->BindAction(LeftAction, ETriggerEvent::Triggered, this, &UITTWidget_CharacterSelect::InputLeft_Player2);
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
	if (SelectCharacter_Player1 != EITTCharacter_Player::None)
	{
		bConfirm_Player1 = true;
		CheckConfirm();
	}

	UpdateDesign_BTN();
}

void UITTWidget_CharacterSelect::InputRight_Player1()
{
	if (SelectCharacter_Player1 == EITTCharacter_Player::None && SelectCharacter_Player2 != EITTCharacter_Player::Cody)
	{
		SelectCharacter_Player1 = EITTCharacter_Player::Cody;
	}
	
	if (SelectCharacter_Player1 == EITTCharacter_Player::May)
	{
		SelectCharacter_Player1 = EITTCharacter_Player::None;
		
		bConfirm_Player1 = false;
	}

	UpdateDesign_BTN();
}

void UITTWidget_CharacterSelect::InputLeft_Player1()
{
	if (SelectCharacter_Player1 == EITTCharacter_Player::None && SelectCharacter_Player2 != EITTCharacter_Player::May)
	{
		SelectCharacter_Player1 = EITTCharacter_Player::May;
	}
	
	if (SelectCharacter_Player1 == EITTCharacter_Player::Cody)
	{
		SelectCharacter_Player1 = EITTCharacter_Player::None;
		
		bConfirm_Player1 = false;
	}

	UpdateDesign_BTN();
}


// -- Player2 -- //
void UITTWidget_CharacterSelect::InputConfirm_Player2()
{
	if (SelectCharacter_Player2 != EITTCharacter_Player::None)
	{
		bConfirm_Player2 = true;
		CheckConfirm();
	}
	
	UpdateDesign_BTN();
}

void UITTWidget_CharacterSelect::InputRight_Player2()
{
	if (SelectCharacter_Player2 == EITTCharacter_Player::None && SelectCharacter_Player1 != EITTCharacter_Player::Cody)
	{
		SelectCharacter_Player2 = EITTCharacter_Player::Cody;
	}
	
	if (SelectCharacter_Player2 == EITTCharacter_Player::May)
	{
		SelectCharacter_Player2 = EITTCharacter_Player::None;
		
		bConfirm_Player2 = false;
	}

	UpdateDesign_BTN();
}

void UITTWidget_CharacterSelect::InputLeft_Player2()
{
	if (SelectCharacter_Player2 == EITTCharacter_Player::None && SelectCharacter_Player1 != EITTCharacter_Player::May)
	{
		SelectCharacter_Player2 = EITTCharacter_Player::May;
	}
	
	if (SelectCharacter_Player2 == EITTCharacter_Player::Cody)
	{
		SelectCharacter_Player2 = EITTCharacter_Player::None;
		
		bConfirm_Player2 = false;
	}

	UpdateDesign_BTN();
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

			GameProcessMgr->AddControllerIdToCharacter(0, SelectCharacter_Player1);
			GameProcessMgr->AddControllerIdToCharacter(1, SelectCharacter_Player2);
		}

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
	
	switch (SelectCharacter_Player1)
	{
	case EITTCharacter_Player::None:
		{
			Visibility_SelectBTN_Player1 = ESlateVisibility::SelfHitTestInvisible;
			break;
		}
		
	case EITTCharacter_Player::Cody:
		{
			Visibility_ConfirmBTN_Right = ESlateVisibility::SelfHitTestInvisible;
			WBP_ConfirmBTN_Right->SetControllerId(0);

			bConfirm_ConfirmBTN_Right = bConfirm_Player1;
			break;
		}

	case EITTCharacter_Player::May:
		{
			Visibility_ConfirmBTN_Left = ESlateVisibility::SelfHitTestInvisible;
			WBP_ConfirmBTN_Left->SetControllerId(0);

			bConfirm_ConfirmBTN_Left = bConfirm_Player1;
			break;
		}
	}
	
	switch (SelectCharacter_Player2)
	{
	case EITTCharacter_Player::None:
		{
			Visibility_SelectBTN_Player2 = ESlateVisibility::SelfHitTestInvisible;
			break;
		}
		
	case EITTCharacter_Player::Cody:
		{
			Visibility_ConfirmBTN_Right = ESlateVisibility::SelfHitTestInvisible;
			WBP_ConfirmBTN_Right->SetControllerId(1);
			
			bConfirm_ConfirmBTN_Right = bConfirm_Player2;
			break;
		}

	case EITTCharacter_Player::May:
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
