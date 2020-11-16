// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Psydekick.h"

TArray<UMenuEntryWrapper*> UMenu::WrapEntries()
{
	TArray<UMenuEntryWrapper*> WrappedEntries;
	TArray<int32> Indicies;
	Indicies.Emplace(-1);

	for(int32 GlobalIndex=0; GlobalIndex<Entries.Num(); GlobalIndex++){
		// Manage stack for local index counting
		int32 Cmp = Entries[GlobalIndex].Depth - (Indicies.Num()-1);
		if(Cmp > 0)
		{
			// push
			Indicies.Emplace(-1);
		}
		else if(Cmp < 0)
		{
			// pop
			while(Indicies.Num()-1 > Entries[GlobalIndex].Depth)
			{
				Indicies.RemoveAt(Indicies.Num()-1);
			}
		}
		if(Indicies.Num() == 0)
		{
			UE_LOG(LogPsydekick, Warning, TEXT("UMenu::WrapEntries Underflowed indicies on Idx=%d"), GlobalIndex);
			return WrappedEntries;
		}
		Indicies[Indicies.Num()-1] += 1;

		UMenuEntryWrapper* Wrapper = NewObject<UMenuEntryWrapper>();
		Wrapper->MenuEntry = Entries[GlobalIndex];
		Wrapper->GlobalIndex = GlobalIndex;
		Wrapper->LocalIndex = Indicies[Indicies.Num()-1];
		Wrapper->IsLocalLast = IsLocalLast(GlobalIndex);
		Wrapper->IsGlobalLast = (GlobalIndex == Entries.Num()-1);
		Wrapper->HasChildren = HasChildren(GlobalIndex);

		WrappedEntries.Emplace(Wrapper);
	}

	return WrappedEntries;
}

UMenuEntryWrapper* UMenuEntryWrapper::Conv_MenuEntryToMenuEntryWrapper(FMenuEntry InMenuEntry)
{
	UMenuEntryWrapper* Wrapper = NewObject<UMenuEntryWrapper>();
	Wrapper->MenuEntry = InMenuEntry;

	return Wrapper;
}

bool UMenu::HasChildren(int32 Index)
{
	if(Index < 0 || Index >= Entries.Num())
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenu::HasChildren called with out of range index %d (Num()=%d)"), Index, Entries.Num());
		return false;
	}

	return Index < Entries.Num()-2 && Entries[Index+1].Depth > Entries[Index].Depth;
}

bool UMenu::IsLocalLast(int32 Index)
{
	if(Index < 0 || Index >= Entries.Num())
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenu::IsLocalLast called with out of range index %d (Num()=%d)"), Index, Entries.Num());
		return false;
	}

	return (Index == Entries.Num()-1) || (Entries[Index].Depth > Entries[Index+1].Depth);
}

bool UMenu::GetDescendantRange(int32 Parent, int32 &First, int32 &Last)
{
	if((Parent >= Entries.Num()-1) || (Entries[Parent+1].Depth <= Entries[Parent].Depth))
	{
		return false;
	}

	First = Parent+1;
	for(Last=First; Last<Entries.Num(); Last++)
	{
		if(Entries[Last].Depth <= Entries[Parent].Depth)
		{
			break;
		}
	}
	Last--;

	return true;
}

TArray<FMenuEntry> UMenu::RemoveEntryAndChildren(int32 Index)
{
	TArray<FMenuEntry> RemovedEntries;

	if(Index >= Entries.Num() || Index < 0)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenu::RemoveEntryAndChildren called with out of range index %d (Num()=%d)"), Index, Entries.Num());
		return RemovedEntries;
	}

	int32 DepthLimit = Entries[Index].Depth;
	do
	{
		RemovedEntries.Emplace(Entries[Index]);
		Entries.RemoveAt(Index);
	}while(Index < Entries.Num() && Entries[Index].Depth > DepthLimit);

	return RemovedEntries;
}

void UMenu::RemoveEntryKeepChildren(int32 Parent)
{
	if(Parent >= Entries.Num() || Parent < 0)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenu::RemoveEntryKeepChildren called with out of range index %d (Num()=%d)"), Parent, Entries.Num());
		return;
	}
	for(int32 Index = Parent+1; (Index < Entries.Num() && Entries[Index].Depth > Entries[Parent].Depth); Index++)
	{
		Entries[Index].Depth--;
	}
	Entries.RemoveAt(Parent);
}

void UMenu::SwapAdjacent(int32 A, int32 B)
{
	if(A < 0 || B < 0 || A >= Entries.Num() || B >= Entries.Num())
	{
		UE_LOG(LogPsydekick, Warning, TEXT("Attempt to swap UMenu entries with bad indices %d, %d (Num()=%d)"), A, B, Entries.Num());
		return;
	}

	Entries.Swap(A, B);
	int32 TmpDepth = Entries[A].Depth;
	Entries[A].Depth = Entries[B].Depth;
	Entries[B].Depth = TmpDepth;
}

void UMenu::MoveEntryUp(int32 Index)
{
	SwapAdjacent(Index-1, Index);
}

void UMenu::MoveEntryDown(int32 Index)
{
	SwapAdjacent(Index, Index+1);
}

void UMenu::InsertAt(int32 Index, FString Name)
{
	FMenuEntry Entry;
	Entry.Depth = 0;
	Entry.Name = Name;
	if(Index > 0 && Entries.Num() > 1)
	{
		Entry.Depth = Entries[Index-1].Depth;
	}

	Entries.Insert(Entry, Index);
}

void UMenu::Indent(int32 Index)
{
	if(Index >= Entries.Num() || Index < 0)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenu::Indent called with out of range index %d (Num()=%d)"), Index, Entries.Num());
		return;
	}

	int32 First, Last;
	if(GetDescendantRange(Index, First, Last))
	{
		for(int32 i=First; i<=Last; i++)
		{
			Entries[i].Depth++;
		}
	}
	Entries[Index].Depth++;
}

void UMenu::Outdent(int32 Index)
{
	if(Index >= Entries.Num() || Index < 0)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenu::Outdent called with out of range index %d (Num()=%d)"), Index, Entries.Num());
		return;
	}

	int32 First, Last;
	if(GetDescendantRange(Index, First, Last))
	{
		for(int32 i=First; i<=Last; i++)
		{
			Entries[i].Depth--;
		}
	}
	Entries[Index].Depth--;
}

