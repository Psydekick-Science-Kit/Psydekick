// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Engine/Texture.h"

/**
 *
 */

class PSYDEKICK_API SImageDisplay : public SBorder
{
public:
	SLATE_BEGIN_ARGS(SImageDisplay)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void SetImage(UTexture* ImageTexture);
	void SetBackgroundColor(const FLinearColor Color);
	void SetOffsets(const int32 OffsetX, const int32 OffsetY);

private:
	TSharedPtr<SImage> ImageBox;
	FSlateColorBrush BrushColor = FSlateColorBrush(FLinearColor(0, 0, 0, 0.75));
	FSlateBrush Brush;
};
