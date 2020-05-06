// Fill out your copyright notice in the Description page of Project Settings.

#include "ImageDisplay.h"
#include "SlateOptMacros.h"

#include "Layout/Visibility.h"
#include "Brushes/SlateImageBrush.h"
#include "MediaTexture.h"
#include "Widgets/Images/SImage.h"
#include "Engine/Texture2D.h"

#include "Psydekick.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SImageDisplay::Construct(const FArguments& InArgs)
{
	SetBorderImage(&brushClr);

	ChildSlot
		[
			SAssignNew(ImageBox, SImage)
			.Visibility(EVisibility::Visible)
		];
}

void SImageDisplay::SetImage(UTexture* ImageTexture) {
	Brush.SetResourceObject(ImageTexture);
	if (UTexture2D* Texture2D = Cast<UTexture2D>(ImageTexture)){
		SetVAlign(EVerticalAlignment::VAlign_Center);
		SetHAlign(EHorizontalAlignment::HAlign_Center);

		Brush.ImageSize.X = Texture2D->GetSizeX();
		Brush.ImageSize.Y = Texture2D->GetSizeY();
	}
	else if (UMediaTexture* MediaTexture = Cast<UMediaTexture>(ImageTexture)) {
		SetVAlign(EVerticalAlignment::VAlign_Fill);
		SetHAlign(EHorizontalAlignment::HAlign_Fill);
	}

	ImageBox->SetImage(&Brush);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
