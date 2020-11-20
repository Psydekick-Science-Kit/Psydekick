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
	UPROPERTY(BlueprintReadWrite, Category = "Psydekick|Utilities")
	TArray<UObject*> SourcePool;

	UPROPERTY(BlueprintReadWrite, Category = "Psydekick|Utilities")
	TArray<UObject*> CurrentPool;

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Utilities", meta=(DeterminesOutputType = "AsClass"))
	UObject* GetNext(TSubclassOf<UObject> AsClass);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Utilities", meta=(DeterminesOutputType = "AsClass"))
	UObject* GetRandom(TSubclassOf<UObject> AsClass);
};
