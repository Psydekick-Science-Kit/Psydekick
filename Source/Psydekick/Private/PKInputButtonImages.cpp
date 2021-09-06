// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "PKInputButtonImages.h"

#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerInput.h"

UTexture2D* UPKInputButtonImages::FromKey(FKey Key)
{
	if(Key == EKeys::Gamepad_FaceButton_Top)
	{
		return FaceTop;
	}
	if(Key == EKeys::Gamepad_FaceButton_Right)
	{
		return FaceRight;
	}
	if(Key == EKeys::Gamepad_FaceButton_Bottom)
	{
		return FaceBottom;
	}
	if(Key == EKeys::Gamepad_FaceButton_Left)
	{
		return FaceLeft;
	}

	return nullptr;
}

UTexture2D* UPKInputButtonImages::FromAction(FName Action)
{
	TArray<FInputActionKeyMapping> ActionMappings;

	UInputSettings* InputSettings = UInputSettings::GetInputSettings();
	InputSettings->GetActionMappingByName(Action, ActionMappings);

	for(FInputActionKeyMapping ActionMapping : ActionMappings)
	{
		UTexture2D* Image = FromKey(ActionMapping.Key);
		if(Image)
		{
			return Image;
		}
	}

	return nullptr;
}
