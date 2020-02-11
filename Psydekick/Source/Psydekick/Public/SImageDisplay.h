// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Slate.h"
#include "Styling/SlateBrush.h" 

//#include "GameFramework/HUD.h" 

/**
 *
 */
class PSYDEKICK_API SImageDisplay : public SBorder
{
public:
	SLATE_BEGIN_ARGS(SImageDisplay)
	{}
	SLATE_END_ARGS()

		/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void SetImage(UTexture* ImageTexture);

private:
	TSharedPtr<SImage> ImageBox;
	FSlateColorBrush brushClr = FSlateColorBrush(FLinearColor(0, 0, 0, 0.5));
	FSlateBrush Brush;

};
