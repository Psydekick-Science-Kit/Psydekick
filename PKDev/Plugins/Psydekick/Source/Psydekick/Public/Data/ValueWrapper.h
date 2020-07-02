#pragma once

#include "ValueWrapper.generated.h"


UCLASS(BlueprintType)
class PSYDEKICK_API UValueWrapper : public UObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class PSYDEKICK_API UBooleanWrapper : public UValueWrapper
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool Value;
};

UCLASS(BlueprintType)
class UStringWrapper : public UValueWrapper
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString Value;
};

USTRUCT(BlueprintType)
struct FValueArrayWrapper
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<UValueWrapper*> Array;
};
