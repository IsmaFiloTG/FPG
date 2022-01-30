#include "MenuTools/MenuToolExample.h"
#include "FPGEditor.h"
#include "Widgets/SWindow.h"

#define LOCTEXT_NAMESPACE "MenuToolExample"

class MenuToolExampleCommands : public TCommands<MenuToolExampleCommands>
{
public:

    MenuToolExampleCommands()
        : TCommands<MenuToolExampleCommands>(
            TEXT("MenuToolExample"), // Context name for fast lookup
            FText::FromString("Example Menu tool"), // Context name for displaying
            NAME_None,   // No parent context
            FEditorStyle::GetStyleSetName() // Icon Style Set
            )
    {
    }

    virtual void RegisterCommands() override
    {
        UI_COMMAND(MenuCommand1, "Menu Command 1", "Test Menu Command 1.", EUserInterfaceActionType::Button, FInputGesture());

    }

public:
    TSharedPtr<FUICommandInfo> MenuCommand1;
};

void MenuToolExample::MapCommands()
{
    const auto& Commands = MenuToolExampleCommands::Get();

    CommandList->MapAction(
        Commands.MenuCommand1,
        FExecuteAction::CreateSP(this, &MenuToolExample::MenuCommand1),
        FCanExecuteAction());
}

void MenuToolExample::OnStartupModule()
{
    CommandList = MakeShareable(new FUICommandList);
    MenuToolExampleCommands::Register();
    MapCommands();
    FFPGEditorModule::Get().AddMenuExtension(
        FMenuExtensionDelegate::CreateRaw(this, &MenuToolExample::MakeMenuEntry),
        FName("Section_1"),
        CommandList);
}

void MenuToolExample::OnShutdownModule()
{
    MenuToolExampleCommands::Unregister();
}

void MenuToolExample::MakeMenuEntry(FMenuBuilder& menuBuilder)
{
    menuBuilder.AddMenuEntry(MenuToolExampleCommands::Get().MenuCommand1);
}

void MenuToolExample::MenuCommand1()
{
    TSharedPtr<SWindow> testWindow = SNew(SWindow)
        .Title(LOCTEXT("Asset Window", "Asset Window"))
        .ClientSize(FVector2D(30, 20))
        .SupportsMaximize(false)
        .SupportsMinimize(false)
        .SizingRule(ESizingRule::Autosized)
        .AutoCenter(EAutoCenter::PrimaryWorkArea)
        .IsInitiallyMaximized(false)
        .bDragAnywhere(true)
        [
            //SNew(STextBlock)
            //.Text(FText::FromString(TEXT("This is a window example.")))
            
            SNew(SEditableTextBox)
            .OnTextCommitted(FOnTextCommitted::CreateSP(this, &MenuToolExample::DebugText))
        ];

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
}

void MenuToolExample::DebugText(const FText& Text, ETextCommit::Type TextType)
{
    if (TextType == ETextCommit::OnEnter)
    {
        UE_LOG(LogClass, Log, TEXT("%s"), *Text.ToString());
    }
}

#undef LOCTEXT_NAMESPACE