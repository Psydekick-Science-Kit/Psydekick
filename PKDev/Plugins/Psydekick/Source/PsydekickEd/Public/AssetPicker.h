#pragma once

#include "SPKAssetPicker.h"
#include "Widgets/SWidget.h"
#include "Components/ContentWidget.h"

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "AssetPicker.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClassSelected, UClass*, Class);

UCLASS()
class PSYDEKICKED_API UAssetPicker : public UContentWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="Miscellaneous")
	FOnClassSelected ClassSelected;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SPKAssetPicker> SlatePicker;

	UFUNCTION()
	void OnClassSelected(UClass* Class);
};
