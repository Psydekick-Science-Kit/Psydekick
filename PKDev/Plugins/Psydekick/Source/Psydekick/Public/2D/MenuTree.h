// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Blueprint/UserWidget.h"

#include "MenuTree.generated.h"

USTRUCT(BlueprintType)
struct FMenuTreeEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Menu")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Menu")
	int32 Depth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Menu")
	UClass* WidgetClass = nullptr;
};

UCLASS(BlueprintType)
class PSYDEKICK_API UMenuTree : public UObject
{
	GENERATED_BODY()

	#pragma region Properties
public:
	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	TArray<FMenuTreeEntry> Entries;
	#pragma endregion

	#pragma region Functions
public:
	UFUNCTION(BlueprintPure, Category = "Psydekick|Menu")
	int32 GetParent(int32 Index);

	UFUNCTION(BlueprintPure, Category = "Psydekick|Menu")
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
	TArray<FMenuTreeEntry> RemoveEntryAndChildren(int32 Parent);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	void MoveEntryUp(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	void MoveEntryDown(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	void InsertAt(int32 Index, FString Name);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Menu")
	TArray<UMenuTreeEntryWrapper*> WrapEntries();

protected:
	void SwapAdjacent(int32 A, int32 B);

	#pragma endregion

};

UCLASS(BlueprintType)
class PSYDEKICK_API UMenuTreeEntryWrapper : public UObject {
	GENERATED_BODY()

	#pragma region Properties
public:
	UPROPERTY(BlueprintReadWrite, Category="MenuTree")
	FMenuTreeEntry MenuTreeEntry;

	UPROPERTY(BlueprintReadWrite, Category="MenuTree")
	int32 GlobalIndex;

	UPROPERTY(BlueprintReadWrite, Category="MenuTree")
	int32 LocalIndex;

	UPROPERTY(BlueprintReadWrite, Category="MenuTree")
	int32 ParentIndex;

	UPROPERTY(BlueprintReadWrite, Category="MenuTree")
	bool IsLocalLast;

	UPROPERTY(BlueprintReadWrite, Category="MenuTree")
	bool IsGlobalLast;

	UPROPERTY(BlueprintReadWrite, Category="MenuTree")
	bool HasChildren;
	#pragma endregion

	#pragma region Functions
public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MenuEntry To Menu Entry Wrapper", CompactNodeTitle = "Wrap", BlueprintAutocast), Category = "Psydekick")
	static UMenuTreeEntryWrapper* Conv_MenuEntryToMenuEntryWrapper(FMenuTreeEntry InMenuEntry);
	#pragma endregion

};
