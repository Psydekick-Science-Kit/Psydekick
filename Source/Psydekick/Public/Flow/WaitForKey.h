// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Components/InputComponent.h"

#include "Tickable.h"

#include "WaitForKey.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKeyPressedExec, FKey, Key);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitKeyTimedOutExec);

DECLARE_DELEGATE(FOnTimeoutComplete);

UCLASS()
class PSYDEKICK_API UWaitForKey : public UBlueprintAsyncActionBase, public FTickableGameObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FKeyPressedExec KeyPressed;

	UPROPERTY(BlueprintAssignable)
	FWaitKeyTimedOutExec TimedOut;

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Wait For Key (latent)"), Category = "Psydekick|Flow|Events")
	static UWaitForKey* WaitForKey(const UObject* WorldContextObject, const TArray<FKey> Keys, const float Timeout);

	void OnTimeoutTriggered();
	void OnKeyPress(FKey Key);

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual bool IsTickableInEditor() const override;
	virtual bool IsTickableWhenPaused() const override;

	virtual TStatId GetStatId() const override;

protected:
	bool bActive;
	const UObject* WorldContextObject;
	FTimerHandle TimeoutHandle;
	TArray<FKey> Keys;

	FOnTimeoutComplete TimeoutTriggered;
	float Timeout;

	TArray<FInputKeyBinding> KeyBindings;
};
