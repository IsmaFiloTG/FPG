#include "TabTools/FPGBaseTab.h"

#pragma once

class TabToolExample : public FFPGBaseTab
{
public:
    virtual ~TabToolExample() {}
    virtual void OnStartupModule() override;
    virtual void OnShutdownModule() override;
    virtual void Initialize() override;
    virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs) override;
};