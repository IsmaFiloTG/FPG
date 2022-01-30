// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Slate.h"
#include "TableSubsystem.generated.h"

UENUM(BlueprintType)
enum ENotificationType
{
	Error		 UMETA(DisplayName = "Error"),
	Warning      UMETA(DisplayName = "Warning"),
	Info		 UMETA(DisplayName = "Info"),
	Success		 UMETA(DisplayName = "Success"),
};

UCLASS()
class FPG_API UTableSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool ImportStringTableFromCSV(class UStringTable* Table, FString FilePath);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	class UTableRegistry* FindTableRegistry();

	UFUNCTION(BlueprintCallable, BlueprintPure) 
	FString ReadScriptFile(FString filename);

	UFUNCTION(BlueprintCallable)
	void ShowNotification(FText Text, const ENotificationType Type);

	UFUNCTION(BlueprintCallable)
	void ErrorNotification(const FText& text, FSlateBrush Image);

	
};
