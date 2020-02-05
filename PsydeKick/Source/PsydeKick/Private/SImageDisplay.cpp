// Fill out your copyright notice in the Description page of Project Settings.


#include "SImageDisplay.h"
#include "SlateOptMacros.h"

#include <Runtime\SlateCore\Public\Layout\Visibility.h>
#include "Brushes/SlateImageBrush.h" 


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SImageDisplay::Construct(const FArguments& InArgs)
{
	SetBorderImage(&brushClr);

	ChildSlot
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SAssignNew(ImageBox, SImage)
			.Visibility(EVisibility::Visible)
		];
}

void SImageDisplay::SetImage(UTexture2D* ImageTexture) {
	Brush.SetResourceObject(ImageTexture);
	Brush.ImageSize.X = ImageTexture->GetSizeX();
	Brush.ImageSize.Y = ImageTexture->GetSizeY();

	ImageBox->SetImage(&Brush);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
