// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "2D/PsydekickVisuals2D_BPLibrary.h"
#include "2D/PsydekickVisuals2D.h"
#include "Psydekick.h"

#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

THIRD_PARTY_INCLUDES_START
	#include <SDL.h>
	#include <SDL_joystick.h>
THIRD_PARTY_INCLUDES_END

APsydekickVisuals2D* UPsydekickVisuals2D_BPLibrary::PKVisuals2DActor;

APsydekickVisuals2D* UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(const UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();

	TArray<AActor*> Instances;
	UGameplayStatics::GetAllActorsOfClass(World, APsydekickVisuals2D::StaticClass(), Instances);

	bool NeedToSpawn = (!PKVisuals2DActor) || (Instances.Num() < 1);
	if(!NeedToSpawn)
	{
		PKVisuals2DActor = (APsydekickVisuals2D*)Instances.Last();
		NeedToSpawn = NeedToSpawn || (World != PKVisuals2DActor->GetWorld());
	}

	if(NeedToSpawn)
	{
		UE_LOG(LogPsydekick, Log, TEXT("Spawning new PKVisuals2DActor"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PKVisuals2DActor = World->SpawnActor<APsydekickVisuals2D>(SpawnParams);
	}

	return PKVisuals2DActor;
}

void UPsydekickVisuals2D_BPLibrary::ShowText(const UObject* WorldContextObject, const FString Text, const float Duration, const FLinearColor TextColor, const FLinearColor BackgroundColor, const ETextJustify::Type Justification, const bool AutoWrapText)
{
	UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->ShowText(Text, Duration, TextColor, BackgroundColor, Justification, AutoWrapText);
}

void UPsydekickVisuals2D_BPLibrary::ClearScreen(const UObject* WorldContextObject, const bool PsydekickWidgetOnly)
{
	UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->ClearScreen(PsydekickWidgetOnly);
}

void UPsydekickVisuals2D_BPLibrary::ClearTexts(const UObject* WorldContextObject)
{
	UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->ClearTexts();
}

void UPsydekickVisuals2D_BPLibrary::ClearImages(const UObject* WorldContextObject)
{
	UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->ClearImages();
}

void UPsydekickVisuals2D_BPLibrary::ShowImage(const UObject* WorldContextObject, UTexture* Image, FLinearColor BackgroundColor, EVerticalAlignment VAlign, EHorizontalAlignment HAlign, int32 OffsetX, int OffsetY)
{
	UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->ShowImage(Image, BackgroundColor, VAlign, HAlign, OffsetX, OffsetY);
}

void UPsydekickVisuals2D_BPLibrary::GetChoice(const UObject* WorldContextObject, const FString Prompt, const TArray<FString> Options, const FChoiceMade &ChoiceMade)
{
	UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->GetChoice(Prompt, Options, ChoiceMade);
}

void UPsydekickVisuals2D_BPLibrary::SetUIMode(const UObject* WorldContextObject)
{
	UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->SetUIMode();
}

void UPsydekickVisuals2D_BPLibrary::SetGameOnlyMode(const UObject* WorldContextObject)
{
	UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->SetGameOnlyMode();
}

TArray<FGamepadInfo> UPsydekickVisuals2D_BPLibrary::GetGamepadInfo()
{
	TArray<FGamepadInfo> Gamepads;

	SDL_Init(SDL_INIT_JOYSTICK);

	int JoystickCount = SDL_NumJoysticks();

	UE_LOG(LogPsydekick, Log, TEXT("Found %d Joysticks"), JoystickCount);

	for(int i = 0; i < JoystickCount; i++)
	{
		SDL_Joystick* Joystick = SDL_JoystickOpen(i);
		if (Joystick)
		{
			SDL_JoystickGUID SDL_guid = SDL_JoystickGetGUID(Joystick);
			char GuidStr[1024];
			SDL_JoystickGetGUIDString(SDL_guid, GuidStr, sizeof(GuidStr));
			const char* NameStr = SDL_JoystickName(Joystick);

			SDL_JoystickClose(Joystick);

			FString Guid(GuidStr);
			FString Name(NameStr);

			FGamepadInfo Gamepad;
			Gamepad.Guid = Guid;
			Gamepad.Name = Name;

			Gamepads.Add(Gamepad);
		}
	}

	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	Gamepads.Shrink();

	return Gamepads;
}

bool UPsydekickVisuals2D_BPLibrary::IsXboxGamepadConnected()
{
	TArray<FGamepadInfo> Gamepads = GetGamepadInfo();
	for(FGamepadInfo Gamepad : Gamepads)
	{
		if(Gamepad.Guid.StartsWith("030000005e04")){
			return true;
		}
	}

	return false;
}
