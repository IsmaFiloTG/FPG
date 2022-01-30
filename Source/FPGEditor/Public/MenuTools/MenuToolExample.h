#include "IFPGModuleInterface.h"

class MenuToolExample : public IFPGModuleListenerInterface, public TSharedFromThis<MenuToolExample>
{
public:
    virtual ~MenuToolExample() {}

    virtual void OnStartupModule() override;
    virtual void OnShutdownModule() override;

    void MakeMenuEntry(FMenuBuilder& menuBuilder);

protected:
    TSharedPtr<FUICommandList> CommandList;

    void MapCommands();

    // UI Command functions
    void MenuCommand1();

    void DebugText(const FText& Text, ETextCommit::Type TextType);
};