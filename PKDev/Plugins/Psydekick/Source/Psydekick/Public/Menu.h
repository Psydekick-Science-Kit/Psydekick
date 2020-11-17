// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Menu.generated.h"


USTRUCT(BlueprintType)
struct FMenuEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Psydekick")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Psydekick")
	int32 Depth;
};


UCLASS(BlueprintType)
class PSYDEKICK_API UMenu : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	TArray<FMenuEntry> Entries;

	UFUNCTION(BlueprintPure)
	int32 GetParent(int32 Index);

	UFUNCTION(BlueprintPure)
	TArray<int32> GetAncestors(int32 Index);

	UFUNCTION(BlueprintPure, Category = "Psydekick|Menu")
	TArray<int32> GetChildren(int32 Parent);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	void Indent(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	void Outdent(int32 Index);

	UFUNCTION(BlueprintPure, Category = "Psydekick|Menu")
	bool HasChildren(int32 Index);

	UFUNCTION(BlueprintPure, Category = "Psydekick|Menu")
	bool IsLocalLast(int32 Index);

	UFUNCTION(BlueprintPure, Category = "Psydekick|Menu")
	bool GetDescendantRange(int32 Parent, int32 &First, int32 &Last);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	void RemoveEntryKeepChildren(int32 Parent);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	TArray<FMenuEntry> RemoveEntryAndChildren(int32 Parent);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	void MoveEntryUp(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	void MoveEntryDown(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	void InsertAt(int32 Index, FString Name);

	void SwapAdjacent(int32 A, int32 B);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	TArray<UMenuEntryWrapper*> WrapEntries();
};

UCLASS(BlueprintType)
class PSYDEKICK_API UMenuEntryWrapper : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FMenuEntry MenuEntry;

	UPROPERTY(BlueprintReadWrite)
	int32 GlobalIndex;

	UPROPERTY(BlueprintReadWrite)
	int32 LocalIndex;

	UPROPERTY(BlueprintReadWrite)
	int32 ParentIndex;

	UPROPERTY(BlueprintReadWrite)
	bool IsLocalLast;

	UPROPERTY(BlueprintReadWrite)
	bool IsGlobalLast;

	UPROPERTY(BlueprintReadWrite)
	bool HasChildren;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MenuEntry To Menu Entry Wrapper", CompactNodeTitle = "Wrap", BlueprintAutocast), Category = "Psydekick")
	static UMenuEntryWrapper* Conv_MenuEntryToMenuEntryWrapper(FMenuEntry InMenuEntry);
};
