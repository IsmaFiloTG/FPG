#include "FPGEditor.h"
#include "IFPGModuleInterface.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Docking/SDockWindow.h"

#pragma once

class FFPGBaseWindow : public IFPGModuleListenerInterface, public TSharedFromThis< FFPGBaseWindow >
{
public:


    virtual ~FFPGBaseWindow() {}
   
    virtual void OnStartupModule() override
    {
        Initialize();

        TSharedPtr<SWindow> TopWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
        if (TopWindow.IsValid())
        {
            //Add as Native
            FSlateApplication::Get().AddWindowAsNativeChild(testWindow.ToSharedRef(), TopWindow.ToSharedRef(), true);
        }
        else
        {

            //Default in case no top window
            FSlateApplication::Get().AddWindow(testWindow.ToSharedRef());
        }

        GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(testWindow.ToSharedRef()));
    };

    virtual void OnShutdownModule() override
    {
    };

    // In this function set WindowName/WindowDisplayName/ToolTipText
    virtual void Initialize() {};
    //virtual TSharedRef<SDockWindow> SpawnWindow(const FSpawnWindowArgs& WindowSpawnArgs) { return SNew(SDockWindow); };

    virtual void MakeMenuEntry(FMenuBuilder& menuBuilder)
    {
        //FGlobalWindowmanager::Get()->PopulateWindowSpawnerMenu(menuBuilder, WindowName);
    };

protected:
    FName WindowName;
    FText WindowDisplayName;
    FText ToolTipText;
};