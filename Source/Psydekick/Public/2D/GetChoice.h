// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "PsydekickVisuals2D_BPLibrary.h"

#include "GetChoice.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChoiceMadeExec, FString, choice, int32, index);

UCLASS()
class PSYDEKICK_API UGetChoice : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FChoiceMadeExec ChoiceMade;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Get Choice (latent)"), Category = "Psydekick|Visuals|2D")
	static UGetChoice* GetChoice(const UObject* WorldContextObject, const FString Prompt, const TArray<FString> Options);

	UFUNCTION()
	void OnChoiceMade(FString Choice, uint8 Index);

	virtual void Activate() override;

private:
	const UObject* WorldContextObject;
	FString Prompt;
	TArray<FString> Options;

	FChoiceMade ChoiceMadeDelegate;
};
