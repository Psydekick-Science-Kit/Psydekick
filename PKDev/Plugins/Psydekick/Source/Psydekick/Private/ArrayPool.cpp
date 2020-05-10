// Fill out your copyright notice in the Description page of Project Settings.

#include "ArrayPool.h"

UObject* UArrayPool::GetNext(TSubclassOf<UObject> AsClass)
{
	if(CurrentPool.Num() == 0)
	{
		CurrentPool.Append(SourcePool);
	}
	if(CurrentPool.Num() > 0)
	{
		return CurrentPool.Pop();
	}
	else{
		return nullptr;
	}

}

UObject* UArrayPool::GetRandom(TSubclassOf<UObject> AsClass)
{
	if(CurrentPool.Num() == 0)
	{
		CurrentPool.Append(SourcePool);
	}
	if(CurrentPool.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, CurrentPool.Num() - 1);
		UObject* Item = CurrentPool[Index];
		CurrentPool.RemoveAt(Index);

		return Item;
	}
	else{
		return nullptr;
	}

}
