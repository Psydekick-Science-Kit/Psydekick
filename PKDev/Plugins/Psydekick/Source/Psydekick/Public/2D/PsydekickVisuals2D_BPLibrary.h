// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Framework/Text/TextLayout.h"

#include "2D/PsydekickVisuals2D.h"

#include "PsydekickVisuals2D_BPLibrary.generated.h"

UCLASS()
class PSYDEKICK_API UPsydekickVisuals2D_BPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	static APsydekickVisuals2D* PKVisuals2DActor;

public:
	static APsydekickVisuals2D* GetPKVisuals2DActor(const UObject* WorldContextObject);

	/**
	 * Displays text on the screen with a colored background, optionally clearing after a specified period.
	 *
	 * @param Text The text to display on the screen
	 * @param Duration How long to display the text (0 for indefinitely)
	 * @param TextColor Color of the text
	 * @param BackgroundColor Color of the background
	 * @param Justification Horizontal justification of the text
	 * @param AutoWrapText Automatically word-wrap
	 */
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

	/**
	 * Displays an image on the screen with a colored background, optionally clearing after a specified period.
	 *
	 * @param Image The image to display
	 * @param BackgroundColor Color of the background
	 * @param VAlign Vertical alignment of the image
	 * @param HAlign Horizontal alignment of the image
	 * @param OffsetX Horizontal offset
	 * @param OffsetY Vertical offset
	 */
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

	/**
	 * Clears UI elements (text, images, etc) from the screen
	 *
	 * @param PsydekickWidgetOnly True to leave non-Psydekick elements
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject, AdvancedDisplay=1))
	static void ClearScreen(const UObject* WorldContextObject, const bool PsydekickWidgetOnly = true);

	/**
	 * Clear Psydekick Text elements from the screen
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void ClearTexts(const UObject* WorldContextObject);

	/**
	 * Clear Psydekick Image elements from the screen
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void ClearImages(const UObject* WorldContextObject);

	/**
	 * Prompt the user with a menu of options
	 *
	 * @param Prompt Text to display as the prompt
	 * @param Options Array of choices
	 * @param ChoiceMade Delegate called after the user has made a selection
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void GetChoice(const UObject* WorldContextObject, const FString Prompt, const TArray<FString> Options, const FChoiceMade& ChoiceMade);

	/**
	 * Enable UI interaction mode
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void SetUIMode(const UObject* WorldContextObject);

	/**
	 * Disables UI interaction mode
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void SetGameOnlyMode(const UObject* WorldContextObject);
};
