#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/StaticMesh.h" 

#include "ArrayPool.generated.h"

UCLASS(BlueprintType)
class UArrayPool : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<UObject*> SourcePool;

	UPROPERTY(BlueprintReadWrite)
	TArray<UObject*> CurrentPool;

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType = "AsClass"))
	UObject* GetNext(TSubclassOf<UObject> AsClass);

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType = "AsClass"))
	UObject* GetRandom(TSubclassOf<UObject> AsClass);
};
