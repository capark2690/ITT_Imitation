// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTDefine_GameBase.generated.h"


// ==================== Enum ==================== //
// ========== GameInstance ========== //
UENUM()
enum class EITTLaunchProcess : uint8
{
	None = 0,
 
	CreateBasicUtility,
	CreateGameManager,
	RegisterTick,
	ProcessFinished,

	End
};
// ================================== //


// ========== Scene ========== //
UENUM(meta=(Bitflags))
enum class EITTSceneType : uint32
{
	// MainScene * 7 / SubScene * 8 / Detail * 8 / Type * 8
	
	None							= 0b0,
	
	TYPE_FullScreenSequence			= 0b01 UMETA(Hidden),
	TYPE_ObjectSequence				= 0b10 UMETA(Hidden),

	
	// Logo
	LOGO							= 0b01 << 16 UMETA(Hidden),
	ProductionLogo					= LOGO | 0b0001 << 8,
	GameLogo						= LOGO | 0b0010 << 8,


	// Title
	TITLE							= 0b10 << 16 UMETA(Hidden),
	Title_MainMenu					= TITLE | 0b0001 << 8,
	LocalPlay_SelectInput			= TITLE | 0b0010 << 8,
	LocalPlay_SelectCharacter		= TITLE | 0b0011 << 8,

	
	// Ch1
	CH1								= 0b01 << 24 UMETA(Hidden),
	
	Ch1_Awakening					= 0b01 << 24	| 0b01 << 16,

	CH1_FuseRunAway					= CH1 | 0b10 << 16 UMETA(Hidden),
	
	Ch1_PowerSwitchOn				= CH1_FuseRunAway | 0b00000001 << 8 | TYPE_FullScreenSequence,
	Ch1_Tutorial_Jump_LedgeGrab		= CH1_FuseRunAway | 0b00000010 << 8,
	
	Ch1_FuseCrab3_RunAway1			= CH1_FuseRunAway | 0b00000011 << 8	| TYPE_ObjectSequence,	// FuseCrab3 : into the glass
	Ch1_Tutorial_GroundPound		= CH1_FuseRunAway | 0b00000100 << 8,
	
	Ch1_FuseCrab3_RunAway2			= CH1_FuseRunAway | 0b00000101 << 8	| TYPE_ObjectSequence,	// FuseCrab3 : Wall Jump
	Ch1_Tutorial_WallJump			= CH1_FuseRunAway | 0b00000110 << 8,
	
	Ch1_FuseCrab3_RunAway3			= CH1_FuseRunAway | 0b00000111 << 8	| TYPE_ObjectSequence,	// FuseCrab3 : to Hatch back room
	Ch1_Tutorial_DoubleJump			= CH1_FuseRunAway | 0b00001000 << 8,
	
	Ch1_FuseCrab3_RunAway4			= CH1_FuseRunAway | 0b00001001 << 8 | TYPE_ObjectSequence,	// FuseCrab3 : on the GrindStone
	Ch1_Tutorial_Crouch_WallSlide	= CH1_FuseRunAway | 0b00001010 << 8,
	
	Ch1_FuseCrab3_RunAway5			= CH1_FuseRunAway | 0b00001011 << 8 | TYPE_ObjectSequence,	// FuseCrab3 : Turn around the alley
	Ch1_Post_FuseCrab3_RunAway5		= CH1_FuseRunAway | 0b00001100 << 8,
	
	Ch1_FuseCrab3_RunAway6			= CH1_FuseRunAway | 0b00001101 << 8 | TYPE_ObjectSequence,	// FuseCrab3 : Across the broken road
	Ch1_Tutorial_WallSlide2			= CH1_FuseRunAway | 0b00001110 << 8,
	
	Ch1_FuseCrab3_RunAway7			= CH1_FuseRunAway | 0b00001111 << 8 | TYPE_ObjectSequence,	// FuseCrab3 : in front of the chicken wires 
	Ch1_Tutorial_LongJump			= CH1_FuseRunAway | 0b00010000 << 8,
	
	Ch1_FuseCrab3_RunAway8			= CH1_FuseRunAway | 0b00010001 << 8 | TYPE_ObjectSequence,	// FuseCrab3 : in front of the slide
	Ch1_Gimmick_ExtensionCordPlug	= CH1_FuseRunAway | 0b00010010 << 8,
	Ch1_Gimmick_ExtensionCordPlugOn	= CH1_FuseRunAway | 0b00010011 << 8 | TYPE_ObjectSequence,
	Ch1_Gimmick_Tools				= CH1_FuseRunAway | 0b00010100 << 8,

	Ch1_FuseCrab3_RunAway9			= CH1_FuseRunAway | 0b00010101 << 8 | TYPE_ObjectSequence,	// FuseCrab3 : to go down the slide
	Ch1_Gimmick_Slide				= CH1_FuseRunAway | 0b00010110 << 8,
	
	Ch1_PlugInAllFuse				= CH1 | 0b0011 << 16 | TYPE_ObjectSequence,
	Ch1_StairPowerSwitchReady		= CH1 | 0b0100 << 16,
	Ch1_End							= CH1 | 0b0101 << 16	| TYPE_FullScreenSequence
};

UENUM()
enum class EITTLoadingType : uint8
{
	None = 0,

	LoadingWidget,
};
// =========================== //
// ============================================== //


// ==================== Delegate ==================== //
// ========== Level ========== //
DECLARE_DELEGATE_OneParam(FITTOnLoadLevelComplete, const FString&);
// =========================== //
// ================================================== //