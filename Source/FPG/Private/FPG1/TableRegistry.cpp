// Fill out your copyright notice in the Description page of Project Settings.


#include "FPG1/TableRegistry.h"

bool UTableRegistry::DoesTableExist(UObject* Table)
{
    return StoredTables.Contains(Table);
}

FTableInfo UTableRegistry::GetTableInfo(UObject* Table)
{
    return StoredTables[Table];
}

void UTableRegistry::ClearNulledEntries()
{
    while (StoredTables.Contains(nullptr)) 
    {
        StoredTables.Remove(nullptr);
    }
}

void UTableRegistry::ModifyTableInfo(UObject* Table, FTableInfo NewInfo)
{
    StoredTables[Table] = NewInfo;
}

void UTableRegistry::RemoveTable(UObject* Table)
{
    StoredTables.Remove(Table);
}

void UTableRegistry::AddTable(UObject* Table, FTableInfo Info)
{
    StoredTables.Add(Table, Info);
}

TSet<FString> UTableRegistry::GetAllCategories()
{
    TSet<FString> Result;
    for (TPair<UObject*, FTableInfo> MapEntry : StoredTables)
    {
        Result.Append(MapEntry.Value.Categories);
    }
    return Result;
}

TSet<UObject*> UTableRegistry::GetTablesForCategory(FString Category)
{
    TSet<UObject*> Result;
    for (TPair<UObject*, FTableInfo> MapEntry : StoredTables)
    {
        if (MapEntry.Value.Categories.Contains(Category))
            Result.Add(MapEntry.Key);
    }
    return Result;
}



void UTableRegistry::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    ClearNulledEntries();
}