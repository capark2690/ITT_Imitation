// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameBase/GameManager/ITTSingleton.h"
#include "Templates/SubclassOf.h"
#include "ITTWidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class ITT_API UITTWidgetManager : public UObject, public TITTSingleton<UITTWidgetManager>
{
	GENERATED_BODY()

public:
	UITTWidgetManager();
	

	virtual void BuiltInInitialize() override;
	virtual void Finalize() override;

	
	// ========== Create Widget ========== //
	template<typename T>
	TObjectPtr<T> ITTCreateWidgetByTable(const FName& WidgetName, class APlayerController* WidgetOwner = nullptr)
	{
		TObjectPtr<class UITTWidget> Widget = ITTCreateWidgetByTable(WidgetName, WidgetOwner);
		if (Widget == nullptr)
		{
			return nullptr;
		}
		
		return Cast<T>(Widget);
	}

	template<typename T>
	TObjectPtr<T> ITTCreateWidgetByTable_WithOwnerWidget(const FName& WidgetName, class UWidget* WidgetOwner)
	{
		TObjectPtr<class UITTWidget> Widget = ITTCreateWidgetByTable_WithOwnerWidget(WidgetName, WidgetOwner);
		if (Widget == nullptr)
		{
			return nullptr;
		}
		
		return Cast<T>(Widget);
	}

	TObjectPtr<class UITTWidget> ITTCreateWidgetByTable(const FName& WidgetName, class APlayerController* WidgetOwner = nullptr);
	TObjectPtr<class UITTWidget> ITTCreateWidgetByTable_WithOwnerWidget(const FName& WidgetName, class UWidget* WidgetOwner);
	
	TObjectPtr<class UITTWidget> ITTCreateWidgetByClass(TSubclassOf<class UITTWidget> WidgetClass, const FName& WidgetName, APlayerController* WidgetOwner = nullptr, int32 ZOrder = 0);
	TObjectPtr<class UITTWidget> ITTCreateWidgetByClass_WithOwnerWidget(TSubclassOf<class UITTWidget> WidgetClass, const FName& WidgetName, class UWidget* WidgetOwner, int32 ZOrder = 0);
	
private:
	TObjectPtr<class UITTWidget> ITTCreateWidget_Internal(TSubclassOf<class UITTWidget> WidgetClass, const FName& WidgetName, APlayerController* WidgetOwner, int32 ZOrder);
	TObjectPtr<class UITTWidget> ITTCreateWidget_Internal_WithOwnerWidget(TSubclassOf<class UITTWidget> WidgetClass, const FName& WidgetName, class UWidget* WidgetOwner, int32 ZOrder);
	// =================================== //
	
	
private:
	bool bBuiltInInitialized;


#define WidgetMgr UITTWidgetManager::GetInstance()
};