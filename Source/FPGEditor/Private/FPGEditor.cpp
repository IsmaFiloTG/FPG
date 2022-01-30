// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPGEditor.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MenuTools/MenuToolExample.h"
#include "TabTools/TabToolExample.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FFPGEditorModule, FPGEditor, "FPGEditor" );

DEFINE_LOG_CATEGORY(FPGEditor);

#define LOCTEXT_NAMESPACE "FPGEditor"

void FFPGEditorModule::StartupModule()
{
    UE_LOG(FPGEditor, Warning, TEXT("FPGEditor: Log Started"));

    if (!IsRunningCommandlet())
    {
        FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
        LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
        MenuExtender = MakeShareable(new FExtender);
        MenuExtender->AddMenuBarExtension("Help", EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateRaw(this, &FFPGEditorModule::MakePulldownMenu));
        LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);
    }

    IFPGModuleInterface::StartupModule();
}

void FFPGEditorModule::ShutdownModule()
{
    UE_LOG(FPGEditor, Warning, TEXT("FPGEditor: Log Ended"));

    IFPGModuleInterface::ShutdownModule();
}

void FFPGEditorModule::AddModuleListeners()
{
    ModuleListeners.Add(MakeShareable(new MenuToolExample));
    ModuleListeners.Add(MakeShareable(new TabToolExample));

}


TSharedRef<FWorkspaceItem> FFPGEditorModule::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

void FFPGEditorModule::AddMenuExtension(const FMenuExtensionDelegate& extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList>& CommandList, EExtensionHook::Position position)
{
    MenuExtender->AddMenuExtension(extensionHook, position, CommandList, extensionDelegate);
}

void FFPGEditorModule::MakePulldownMenu(FMenuBarBuilder& menuBuilder)
{
    menuBuilder.AddPullDownMenu(
        FText::FromString("FPG"),
        FText::FromString("Open the FPG menu"),
        FNewMenuDelegate::CreateRaw(this, &FFPGEditorModule::FillPulldownMenu),
        "FPG",
        FName(TEXT("FPGeMenu"))
    );
}

void FFPGEditorModule::FillPulldownMenu(FMenuBuilder& menuBuilder)
{
    // just a frame for tools to fill in
    menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 1"));
    menuBuilder.AddMenuSeparator(FName("Section_1"));
    menuBuilder.EndSection();

    menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 2"));
    menuBuilder.AddMenuSeparator(FName("Section_2"));
    menuBuilder.EndSection();
}


#undef LOCTEXT_NAMESPACE

