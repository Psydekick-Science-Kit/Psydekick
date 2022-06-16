// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Framework/Text/TextLayout.h"

#include "2D/PsydekickVisuals2D.h"

#include "PsydekickVisuals2D_BPLibrary.generated.h"

USTRUCT(BlueprintType)
struct FGamepadInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Gamepad")
	FString Guid;

	UPROPERTY(BlueprintReadOnly, Category = "Gamepad")
	FString Name;
};

UCLASS()
class PSYDEKICK_API UPsydekickVisuals2D_BPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	static APsydekickVisuals2D* PKVisuals2DActor;

public:
	static APsydekickVisuals2D* GetPKVisuals2DActor(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject, AdvancedDisplay = 2))
	static void ShowText(
		const UObject* WorldContextObject,
		const FString Text = TEXT("Hello, World!"),
		const float Duration = 0.0f,
		FLinearColor TextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f),
		FLinearColor BackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.75f),
		const ETextJustify::Type Justification = ETextJustify::Center,
		const bool AutoWrapText = true
	);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject, AdvancedDisplay=2))
	static void ShowImage(
		const UObject* WorldContextObject,
		UTexture* Image,
		FLinearColor BackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.75f),
		EVerticalAlignment VAlign = EVerticalAlignment::VAlign_Center,
		EHorizontalAlignment HAlign = EHorizontalAlignment::HAlign_Center,
		int32 OffsetX = 0,
		int32 OffsetY = 0
	);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject, AdvancedDisplay=1))
	static void ClearScreen(const UObject* WorldContextObject, const bool PsydekickWidgetOnly = true);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void ClearTexts(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void ClearImages(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void GetChoice(const UObject* WorldContextObject, const FString Prompt, const TArray<FString> Options, const FChoiceMade& ChoiceMade);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void SetUIMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void SetGameOnlyMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static TArray<FGamepadInfo> GetGamepadInfo();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static bool IsXboxGamepadConnected();
};
