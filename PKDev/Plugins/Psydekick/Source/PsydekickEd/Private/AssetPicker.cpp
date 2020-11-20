#include "AssetPicker.h"
#include "Widgets/SWidget.h"
#include "WidgetBlueprint.h"

TSharedRef<SWidget> UAssetPicker::RebuildWidget()
{
	SlatePicker = SNew(SPKAssetPicker);

	SlatePicker->OnClassPicked.BindUObject(this, &UAssetPicker::OnClassSelected);

	if ( GetChildrenCount() > 0 )
	{
		SlatePicker->SetContent(GetContentSlot()->Content ? GetContentSlot()->Content->TakeWidget() : SNullWidget::NullWidget);
	}

	return SlatePicker.ToSharedRef();
}

void UAssetPicker::OnClassSelected(UClass* Class)
{
	ClassSelected.Broadcast(Class);
}

void UAssetPicker::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	SlatePicker.Reset();
}
