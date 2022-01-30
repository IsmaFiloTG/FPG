#include "WindowTools/WindowToolExample.h"

#pragma once
/*
testWindow = SNew(SWindow)
.Title(LOCTEXT("Asset Window", "Asset Window"))
.ClientSize(FVector2D(30, 20))
.SupportsMaximize(false)
.SupportsMinimize(false)
.SizingRule(ESizingRule::Autosized)
.AutoCenter(EAutoCenter::None)
.IsInitiallyMaximized(false)
.bDragAnywhere(true)
[
	textBlock.ToSharedRef()
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

GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(testWindow.ToSharedRef()));*/