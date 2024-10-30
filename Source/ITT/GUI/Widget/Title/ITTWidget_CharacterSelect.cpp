// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTWidget_CharacterSelect.h"

#include "EnhancedInputComponent.h"

#include "GameBase/GameManager/GameBase/ITTGameProcessManager.h"
#include "GameBase/GameManager/GameBase/ITTSceneManager.h"

#include "Button/ITTWidget_Button_CharacterSelect.h"

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"


UITTWidget_CharacterSelect::UITTWidget_CharacterSelect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), MaxConfirmTime(3.f), ConfirmTime_Player1(0.f), ConfirmTime_Player2(0.f), bInputConfirm_Player1(false), bInputConfirm_Player2(false)
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
	ResetConfirm();
}

void UITTWidget_CharacterSelect::NativeDestruct()
{
	ClearInputActionBindings();
	
	Super::NativeDestruct();
}

void UITTWidget_CharacterSelect::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CheckConfirm();
	CalcConfirmTime(InDeltaTime);
}


// ========== Input Action ========== //
void UITTWidget_CharacterSelect::BindInputAction()
{
	if (APlayerController* Player1 = UGameplayStatics::GetPlayerControllerFromID(this, 0))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player1->InputComponent))
		{
			EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputConfirm_Player1);
			EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Completed, this, &UITTWidget_CharacterSelect::InputStopConfirm_Player1);
	
			EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputRight_Player1);
		
			EnhancedInputComponent->BindAction(LeftAction, ETriggerEvent::Triggered, this, &UITTWidget_CharacterSelect::InputLeft_Player1);
		}
	}

	if (APlayerController* Player2 = UGameplayStatics::GetPlayerControllerFromID(this, 1))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player2->InputComponent))
		{
			EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Started, this, &UITTWidget_CharacterSelect::InputConfirm_Player2);
			EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Completed, this, &UITTWidget_CharacterSelect::InputStopConfirm_Player2);
	
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
		bInputConfirm_Player1 = true;
	}
}

void UITTWidget_CharacterSelect::InputStopConfirm_Player1()
{
	bInputConfirm_Player1 = false;
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

		ConfirmTime_Player1 = 0.f;
		bInputConfirm_Player1 = false;
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

		ConfirmTime_Player1 = 0.f;
		bInputConfirm_Player1 = false;
	}

	UpdateDesign_BTN();
}


// -- Player2 -- //
void UITTWidget_CharacterSelect::InputConfirm_Player2()
{
	if (SelectCharacter_Player2 != EITTCharacter_Player::None)
	{
		bInputConfirm_Player2 = true;
	}
}

void UITTWidget_CharacterSelect::InputStopConfirm_Player2()
{
	bInputConfirm_Player2 = false;
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

		ConfirmTime_Player2 = 0.f;
		bInputConfirm_Player2 = false;
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

		ConfirmTime_Player2 = 0.f;
		bInputConfirm_Player2 = false;
	}

	UpdateDesign_BTN();
}
// =========================== //


// ========== Progress ========== //
void UITTWidget_CharacterSelect::ResetConfirm()
{
	ConfirmTime_Player1 = 0.f;
	ConfirmTime_Player2 = 0.f;
	bInputConfirm_Player1 = false;
	bInputConfirm_Player2 = false;
}

void UITTWidget_CharacterSelect::CalcConfirmTime(float InDeltaTime)
{
	// Player1
	if (bInputConfirm_Player1)
	{
		if (ConfirmTime_Player1 >= MaxConfirmTime)
		{
			bInputConfirm_Player1 = false;
		}
		else
		{
			ConfirmTime_Player1 += InDeltaTime;
		}
	}

	// Player2
	if (bInputConfirm_Player2)
	{
		if (ConfirmTime_Player2 >= MaxConfirmTime)
		{
			bInputConfirm_Player2 = false;
		}
		else
		{
			ConfirmTime_Player2 += InDeltaTime;
		}
	}
}

void UITTWidget_CharacterSelect::CheckConfirm()
{
	if (ConfirmTime_Player1 >= MaxConfirmTime && ConfirmTime_Player2 >= MaxConfirmTime)
	{
		if (GameProcessMgr)
		{
			GameProcessMgr->ResetControllerIdToCharacter();

			GameProcessMgr->AddControllerIdToCharacter(0, SelectCharacter_Player1);
			GameProcessMgr->AddControllerIdToCharacter(1, SelectCharacter_Player2);
		}
		
		if (SceneMgr)
		{
			SceneMgr->ChangeScene(EITTSceneType::Ch1_Start, EITTLoadingType::None, true);
		}
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
	
	switch (SelectCharacter_Player1)
	{
	case EITTCharacter_Player::None:
		Visibility_SelectBTN_Player1 = ESlateVisibility::SelfHitTestInvisible;
		break;

	case EITTCharacter_Player::Cody:
		Visibility_ConfirmBTN_Right = ESlateVisibility::SelfHitTestInvisible;
		WBP_ConfirmBTN_Right->SetControllerId(0);
		break;

	case EITTCharacter_Player::May:
		Visibility_ConfirmBTN_Left = ESlateVisibility::SelfHitTestInvisible;
		WBP_ConfirmBTN_Left->SetControllerId(0);
		break;
	}
	
	switch (SelectCharacter_Player2)
	{
	case EITTCharacter_Player::None:
		Visibility_SelectBTN_Player2 = ESlateVisibility::SelfHitTestInvisible;
		break;

	case EITTCharacter_Player::Cody:
		Visibility_ConfirmBTN_Right = ESlateVisibility::SelfHitTestInvisible;
		WBP_ConfirmBTN_Right->SetControllerId(1);
		break;

	case EITTCharacter_Player::May:
		Visibility_ConfirmBTN_Left = ESlateVisibility::SelfHitTestInvisible;
		WBP_ConfirmBTN_Left->SetControllerId(1);
		break;
	}

	WBP_SelectBTN_Player1->SetVisibility(Visibility_SelectBTN_Player1);
	WBP_SelectBTN_Player2->SetVisibility(Visibility_SelectBTN_Player2);
	WBP_ConfirmBTN_Right->SetVisibility(Visibility_ConfirmBTN_Right);
	WBP_ConfirmBTN_Left->SetVisibility(Visibility_ConfirmBTN_Left);
}
// ============================ //
