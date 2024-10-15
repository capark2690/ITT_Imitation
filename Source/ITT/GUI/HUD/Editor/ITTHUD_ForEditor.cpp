// Fill out your copyright notice in the Description page of Project Settings.


#include "ITTHUD_ForEditor.h"

#include "GameBase//GameManager/GUI/ITTWidgetManager.h"
#include "GUI/Widget/ITTWidget.h"


AITTHUD_ForEditor::AITTHUD_ForEditor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
    HudWidgetClassToDefalutActivation.Empty();
#endif
}


// ========== Hud Widget ========== //
void AITTHUD_ForEditor::CreateHudWidgets()
{
    Super::CreateHudWidgets();

#if WITH_EDITOR
    TArray<TSubclassOf<class UITTWidget>> WidgetClasses;
    HudWidgetClassToDefalutActivation.GetKeys(WidgetClasses);
		
    for(TSubclassOf<class UITTWidget>& WidgetClass : WidgetClasses)
    {
        UITTWidgetManager* WidgetManager = UITTWidgetManager::GetInstance();
        ITTCHECK(WidgetManager != nullptr);

        TObjectPtr<UITTWidget> HudWidget = WidgetManager->ITTCreateWidgetByClass(WidgetClass, GetFNameSafe(WidgetClass));
        ITTCHECK(IsValid(HudWidget));
			
        HudWidgets.Emplace(GetFNameSafe(WidgetClass), HudWidget);

        if (*HudWidgetClassToDefalutActivation.Find(WidgetClass))
        {
            ChangeHudActivation(GetFNameSafe(WidgetClass), true);
        }
    }
#endif
}

void AITTHUD_ForEditor::CloseHudWidgets()
{
    Super::CloseHudWidgets();
}

void AITTHUD_ForEditor::ChangeHudActivation(const FName& HudKey, bool bActive)
{
    Super::ChangeHudActivation(HudKey, bActive);
}
// ================================ //