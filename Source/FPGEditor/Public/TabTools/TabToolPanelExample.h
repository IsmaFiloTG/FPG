#include "Slate.h"
#include "TabTools/TabToolExample.h"

class TabToolPanelExample : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(TabToolPanelExample) {}
        SLATE_ARGUMENT(TWeakPtr<class TabToolExample>, Tool)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

protected:
    TWeakPtr<TabToolExample> tool;
};