// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "Flow/WaitForKey.h"

#include "Psydekick.h"
#include "GameFramework/PlayerController.h"

UWaitForKey* UWaitForKey::WaitForKey(const UObject* WorldContextObject, const TArray<FKey> Keys, const float Timeout)
{
	UWaitForKey* BPNode = NewObject<UWaitForKey>();

	BPNode->WorldContextObject = WorldContextObject;
	BPNode->Keys = Keys;
	BPNode->Timeout = Timeout;

	return BPNode;

}
void UWaitForKey::OnTimeoutTriggered()
{
	TimedOut.Broadcast();
	bActive = false;
}

void UWaitForKey::OnKeyPress(FKey Key)
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimeoutHandle);
	this->KeyPressed.Broadcast(Key);
	bActive = false;
}

void UWaitForKey::Activate()
{
	if(Timeout > 0.0f)
	{
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(
			TimeoutHandle,
			this,
			&UWaitForKey::OnTimeoutTriggered,
			Timeout,
			false
		);
	}

	bActive = true;
}

void UWaitForKey::Tick(float DeltaTime)
{
	UE_LOG(LogPsydekick, Log, TEXT("TICK"));
	APlayerController* Controller = WorldContextObject->GetWorld()->GetFirstPlayerController();
	for(FKey Key : Keys)
	{
		if(Controller->WasInputKeyJustPressed(Key))
		{
			OnKeyPress(Key);
			return;
		}
	}
}

bool UWaitForKey::IsTickable() const
{
	return bActive;
}

bool UWaitForKey::IsTickableInEditor() const
{
	return false;
}

bool UWaitForKey::IsTickableWhenPaused() const
{
	return false;
}

TStatId UWaitForKey::GetStatId() const
{
	return TStatId();
}