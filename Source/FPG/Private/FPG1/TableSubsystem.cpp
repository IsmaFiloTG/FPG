// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG1/TableSubsystem.h"
#include "FPG1/TableRegistry.h"

#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"
#include "Internationalization/StringTableRegistry.h"

#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"

#include "EditorAssetLibrary.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Slate.h"
#include "Engine/GameEngine.h"
#include "Delegates/Delegate.h"


bool UTableSubsystem::ImportStringTableFromCSV(UStringTable* Table, FString FilePath)
{
	Table->Modify();
	return Table->GetMutableStringTable()->ImportStrings(FilePath);
}

UTableRegistry* UTableSubsystem::FindTableRegistry()
{
	TArray<FAssetData> AssetsFound;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByClass("TableRegistry", AssetsFound);

	if (AssetsFound.Num() != 1)
	{
		//TODO: log this
		return nullptr;
	}

	FAssetData TableRegistryDataAsset = AssetsFound[0];

	FString Package = TableRegistryDataAsset.PackagePath.ToString();
	FString Name = TableRegistryDataAsset.AssetName.ToString();

	TArray< FStringFormatArg > Args;
	Args.Add(FStringFormatArg(Package));
	Args.Add(FStringFormatArg(Name));

	FString AssetPath = FString::Format(TEXT("{0}/{1}.{1}"), Args);

	UObject* Asset = UEditorAssetLibrary::LoadAsset(AssetPath);
	UTableRegistry* TableRegistry = Cast<UTableRegistry>(Asset);

	if (!TableRegistry)
	{
		//TODO: log this
		return nullptr;
	}

	return TableRegistry;


}

FString UTableSubsystem::ReadScriptFile(FString filename)
{

	FString directory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Content\\01_GDriveTableImporter\\Python\\FPG01_Scripts"));
	FString result;
	UE_LOG(LogClass, Log, TEXT("%s"), *directory);
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();
	if (FPaths::DirectoryExists(*directory)) {
		FString myFile = directory + "/" + filename;
		FFileHelper::LoadFileToString(result, *myFile);
	}
	return result;
}

void UTableSubsystem::ShowNotification(FText Message, const ENotificationType Type) {

	if (FApp::IsUnattended())
	{
		switch (Type)
		{
		case ENotificationType::Error:
			UE_LOG(LogBlueprint, Error, TEXT("%s"), *Message.ToString());
			break;
		case ENotificationType::Warning:
			UE_LOG(LogBlueprint, Warning, TEXT("%s"), *Message.ToString());
			break;
		case ENotificationType::Info:
			UE_LOG(LogBlueprint, Log, TEXT("%s"), *Message.ToString());
			break;
		}
	}
	else
	{
		FNotificationInfo Notification(Message);
		Notification.ExpireDuration = 5.0f;
		Notification.bFireAndForget = true;
		switch (Type)
		{
		case ENotificationType::Error:
			Notification.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Error"));
			break;
		case ENotificationType::Warning:
			Notification.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Warning"));
			break;
		case ENotificationType::Info:
			Notification.bUseSuccessFailIcons = true;
			break;
		case ENotificationType::Success:
			Notification.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Note"));
			break;
		}

		FSlateNotificationManager::Get().AddNotification(Notification);
	}
}

void UTableSubsystem::ErrorNotification(const FText& text, FSlateBrush Image)
{
    FNotificationInfo info(text);
    info.bFireAndForget = true;
    info.FadeInDuration = 0.5f;
    info.FadeOutDuration = 1.0f;
    info.ExpireDuration = 4.0f;
	info.bUseSuccessFailIcons = true;
    info.Image = &Image;


	FSlateNotificationManager& NotManager = FSlateNotificationManager::Get();
	NotManager.AddNotification(info);

}