// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameBase/GameManager/ITTSingleton.h"
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

	
public:
	// ========== Create Widget ========== //
	TObjectPtr<class UITTWidget> ITTCreateWidgetByTable(const FName& WidgetName, APlayerController* WidgetOwner = nullptr, bool bManaged = true, const FName& ManagedWidgetKey = FName());

	template<typename T>
	TObjectPtr<T> ITTCreateWidgetByTable(const FName& WidgetName, APlayerController* WidgetOwner = nullptr, bool bManaged = true, const FName& ManagedWidgetKey = FName())
	{
		TObjectPtr<class UITTWidget> Widget = ITTCreateWidgetByTable(WidgetName, WidgetOwner, bManaged, ManagedWidgetKey);
		if (Widget == nullptr)
		{
			return nullptr;
		}
		
		return Cast<T>(Widget);
	}

	TObjectPtr<class UITTWidget> ITTCreateWidgetByClass(TSubclassOf<class UITTWidget> WidgetClass, const FName& WidgetName, APlayerController* WidgetOwner = nullptr, bool bManaged = false, const FName& ManagedWidgetKey = FName(), int32 ZOrder = 0);
	
private:
	TObjectPtr<class UITTWidget> ITTCreateWidget_Internal(TSubclassOf<class UITTWidget> WidgetClass, const FName& WidgetName, APlayerController* WidgetOwner, bool bManaged, const FName& ManagedWidgetKey, int32 ZOrder);
	// =================================== //

	
public:
	// ========== Destroy Widget ========== //
	bool ITTDestroyWidget(const FName& ManagedWidgetKey, bool bImmediately = false);
	// ==================================== //
	
	
private:
	bool bBuiltInInitialized;

	
	UPROPERTY()
	TMap<FName, TWeakObjectPtr<UITTWidget>> ManagedWidgets;


#define WidgetMgr UITTWidgetManager::GetInstance()
};