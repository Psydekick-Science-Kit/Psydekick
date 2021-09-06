// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "2D/MenuTree.h"

#include "Psydekick.h"

TArray<UMenuTreeEntryWrapper*> UMenuTree::WrapEntries()
{
	TArray<UMenuTreeEntryWrapper*> WrappedEntries;
	TArray<int32> Counts;
	TArray<int32> Ancestors;

	Ancestors.Emplace(-1);
	Counts.Emplace(-1);

	for(int32 GlobalIndex=0; GlobalIndex<Entries.Num(); GlobalIndex++){
		// Manage stack for local index counting
		int32 Cmp = Entries[GlobalIndex].Depth - (Counts.Num()-1);
		if(Cmp > 0)
		{
			// push
			Ancestors.Push(GlobalIndex-1);
			Counts.Emplace(-1);
		}
		else if(Cmp < 0)
		{
			// pop
			while(Counts.Num()-1 > Entries[GlobalIndex].Depth)
			{
				Ancestors.RemoveAt(Ancestors.Num()-1);
				Counts.RemoveAt(Counts.Num()-1);
			}
		}
		if(Counts.Num() == 0)
		{
			UE_LOG(LogPsydekick, Warning, TEXT("UMenuTree::WrapEntries Underflowed Counts on Idx=%d"), GlobalIndex);
			return WrappedEntries;
		}
		Counts[Counts.Num()-1] += 1;

		UMenuTreeEntryWrapper* Wrapper = NewObject<UMenuTreeEntryWrapper>();
		Wrapper->MenuTreeEntry = Entries[GlobalIndex];
		Wrapper->GlobalIndex = GlobalIndex;
		Wrapper->LocalIndex = Counts[Counts.Num()-1];
		Wrapper->IsLocalLast = IsLocalLast(GlobalIndex);
		Wrapper->IsGlobalLast = (GlobalIndex == Entries.Num()-1);
		Wrapper->ParentIndex = Ancestors[Ancestors.Num()-1];
		Wrapper->HasChildren = HasChildren(GlobalIndex);

		WrappedEntries.Emplace(Wrapper);
	}

	return WrappedEntries;
}

UMenuTreeEntryWrapper* UMenuTreeEntryWrapper::Conv_MenuEntryToMenuEntryWrapper(FMenuTreeEntry InMenuTreeEntry)
{
	UMenuTreeEntryWrapper* Wrapper = NewObject<UMenuTreeEntryWrapper>();
	Wrapper->MenuTreeEntry = InMenuTreeEntry;

	return Wrapper;
}

bool UMenuTree::HasChildren(int32 Index)
{
	if(Index < 0 || Index >= Entries.Num())
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenuTree::HasChildren called with out of range index %d (Num()=%d)"), Index, Entries.Num());
		return false;
	}

	return Index < Entries.Num()-1 && Entries[Index+1].Depth > Entries[Index].Depth;
}

bool UMenuTree::IsLocalLast(int32 Index)
{
	if(Index < 0 || Index >= Entries.Num())
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenuTree::IsLocalLast called with out of range index %d (Num()=%d)"), Index, Entries.Num());
		return false;
	}

	return (Index == Entries.Num()-1) || (Entries[Index].Depth > Entries[Index+1].Depth);
}

int32 UMenuTree::GetParent(int32 Index)
{
	int32 TargetDepth = Entries[Index].Depth-1;
	while(--Index>-1 && Entries[Index].Depth > TargetDepth);

	return Index;
}

TArray<int32> UMenuTree::GetAncestors(int32 Index)
{
	TArray<int32> Ancestors;

	while(Index > -1 && Index < Entries.Num() && Entries[Index].Depth > 0){
		Index = GetParent(Index);
		Ancestors.Emplace(Index);
	}

	return Ancestors;
}

bool UMenuTree::GetDescendantRange(int32 Parent, int32 &First, int32 &Last)
{
	if(Parent < 0)
	{
		if(Entries.Num() > 0)
		{
			First = 0;
			Last = Entries.Num()-1;
			return true;
		}

		return false;
	}

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

TArray<int32> UMenuTree::GetChildren(int32 Index)
{
	TArray<int32> Children;

	int32 First, Last;
	if(GetDescendantRange(Index, First, Last))
	{
		for(int32 i=First; i<=Last; i++)
		{
			if(Entries[i].Depth < Entries[First].Depth)
			{
				// too shallow
				break;
			}
			else if(Entries[i].Depth == Entries[First].Depth)
			{
				// found child
				Children.Emplace(i);
			}
			else
			{
				// too deep
			}
		}
	}

	return Children;
}

TArray<FMenuTreeEntry> UMenuTree::RemoveEntryAndChildren(int32 Index)
{
	TArray<FMenuTreeEntry> RemovedEntries;

	if(Index >= Entries.Num() || Index < 0)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenuTree::RemoveEntryAndChildren called with out of range index %d (Num()=%d)"), Index, Entries.Num());
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

void UMenuTree::RemoveEntryKeepChildren(int32 Parent)
{
	if(Parent >= Entries.Num() || Parent < 0)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenuTree::RemoveEntryKeepChildren called with out of range index %d (Num()=%d)"), Parent, Entries.Num());
		return;
	}
	for(int32 Index = Parent+1; (Index < Entries.Num() && Entries[Index].Depth > Entries[Parent].Depth); Index++)
	{
		Entries[Index].Depth--;
	}
	Entries.RemoveAt(Parent);
}

void UMenuTree::SwapAdjacent(int32 A, int32 B)
{
	if(A < 0 || B < 0 || A >= Entries.Num() || B >= Entries.Num())
	{
		UE_LOG(LogPsydekick, Warning, TEXT("Attempt to swap UMenuTree entries with bad indices %d, %d (Num()=%d)"), A, B, Entries.Num());
		return;
	}

	Entries.Swap(A, B);
	int32 TmpDepth = Entries[A].Depth;
	Entries[A].Depth = Entries[B].Depth;
	Entries[B].Depth = TmpDepth;
}

void UMenuTree::MoveEntryUp(int32 Index)
{
	SwapAdjacent(Index-1, Index);
}

void UMenuTree::MoveEntryDown(int32 Index)
{
	SwapAdjacent(Index, Index+1);
}

void UMenuTree::InsertAt(int32 Index, FString Name)
{
	FMenuTreeEntry Entry;
	Entry.Depth = 0;
	Entry.Name = Name;
	if(Index > 0 && Entries.Num() > 1)
	{
		Entry.Depth = Entries[Index-1].Depth;
	}

	Entries.Insert(Entry, Index);
}

void UMenuTree::Indent(int32 Index)
{
	if(Index >= Entries.Num() || Index < 0)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenuTree::Indent called with out of range index %d (Num()=%d)"), Index, Entries.Num());
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

void UMenuTree::Outdent(int32 Index)
{
	if(Index >= Entries.Num() || Index < 0)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UMenuTree::Outdent called with out of range index %d (Num()=%d)"), Index, Entries.Num());
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

