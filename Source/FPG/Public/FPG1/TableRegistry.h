// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TableRegistry.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FTableInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ImportedTableInfo")
	FString URL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ImportedTableInfo")
	TSet<FString> Categories;

};


UCLASS(BlueprintType)
class FPG_API UTableRegistry : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ImportedTables")
	TMap<UObject*, FTableInfo> StoredTables;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ImportedTables")
	bool DoesTableExist(UObject* Table);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ImportedTables")
	FTableInfo GetTableInfo(UObject* Table);

	UFUNCTION(BlueprintCallable, Category = "ImportedTables")
	void ModifyTableInfo(UObject* Table, FTableInfo NewInfo);

	UFUNCTION(BlueprintCallable, Category = "ImportedTables")
	void RemoveTable(UObject* Table);

	UFUNCTION(BlueprintCallable, Category = "ImportedTables")
	void AddTable(UObject* Table, FTableInfo Info);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Categories")
	TSet<FString> GetAllCategories();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Categories")
	TSet<UObject*> GetTablesForCategory(FString Category);

	void ClearNulledEntries();

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

};



