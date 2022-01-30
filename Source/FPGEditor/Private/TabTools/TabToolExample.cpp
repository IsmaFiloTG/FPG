#include "TabTools/TabToolExample.h"
#include "FPGEditor.h"
#include "TabTools/TabToolPanelExample.h"

void TabToolExample::OnStartupModule()
{
    FFPGBaseTab::OnStartupModule();
    FFPGEditorModule::Get().AddMenuExtension(FMenuExtensionDelegate::CreateRaw(this, &TabToolExample::MakeMenuEntry), FName("Section_2"));
}

void TabToolExample::OnShutdownModule()
{
    FFPGBaseTab::OnShutdownModule();
}

void TabToolExample::Initialize()
{
    TabName = "TabTool";
    TabDisplayName = FText::FromString("Tab Tool");
    ToolTipText = FText::FromString("Tab Tool Window");
}

TSharedRef<SDockTab> TabToolExample::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
    TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(TabToolPanelExample)
            .Tool(SharedThis(this))
        ];

    return SpawnedTab;
}