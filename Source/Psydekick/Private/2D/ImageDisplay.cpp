// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "2D/ImageDisplay.h"

#include "Psydekick.h"

#include "MediaTexture.h"
#include "Engine/Texture2D.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SImageDisplay::Construct(const FArguments& InArgs)
{
	SetBorderImage(&BrushColor);

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

void SImageDisplay::SetOffsets(int32 OffsetX, int32 OffsetY)
{
	FMargin Padding;
	if (ChildSlot.HAlignment == EHorizontalAlignment::HAlign_Right)
	{
		Padding.Right = OffsetX;
	}
	else
	{
		Padding.Left = OffsetX;
	}

	if (ChildSlot.VAlignment == EVerticalAlignment::VAlign_Bottom)
	{
		Padding.Bottom = OffsetY;
	}
	else
	{
		Padding.Top = OffsetY;
	}
	SetPadding(Padding);
}

void SImageDisplay::SetBackgroundColor(const FLinearColor Color)
{
	BrushColor = FSlateColorBrush(Color);
	SetBorderImage(&BrushColor);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
