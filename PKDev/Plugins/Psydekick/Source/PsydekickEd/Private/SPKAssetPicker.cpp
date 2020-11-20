#include "SPKAssetPicker.h"
#include "PropertyCustomizationHelpers.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBlueprint.h"

#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"

void SPKAssetPicker::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SAssignNew(ComboButton, SComboButton)
		.ForegroundColor(FLinearColor::White)
		.ButtonColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f))
		.ButtonStyle(FEditorStyle::Get(), "FlatButton.Success")
		.OnGetMenuContent(this, &SPKAssetPicker::GetClassPicker)
		.ContentPadding(FMargin(1.f))
		.ButtonContent()
		[
			SAssignNew(ContentContainer, SBorder)
			.BorderImage(FStyleDefaults::GetNoBrush())
			.Padding(0.0f)
			[
				InArgs._Content.Widget
			]
		]
	];

	Filter = MakeShareable(new FCustomClassViewerFilter);
	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists;
	Filter->AllowedChildrenOfClasses.Add(UUserWidget::StaticClass());
}

TSharedRef<SWidget> SPKAssetPicker::GetClassPicker()
{
	FClassViewerInitializationOptions Options;
	Options.bShowUnloadedBlueprints = true;
	Options.bIsActorsOnly = false;
	Options.bIsPlaceableOnly = false;
	Options.bEditorClassesOnly = false;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.DisplayMode = EClassViewerDisplayMode::ListView;
	Options.ClassFilter = Filter;

	TSharedRef<SWidget> ClassPicker =
		FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer").
		CreateClassViewer(
			Options,
			FOnClassPicked::CreateSP(this, &SPKAssetPicker::OnClassSelectedFromPicker)
		);
	TSharedRef<SBorder> Border = SNew(SBorder);
	Border->SetBorderBackgroundColor(FLinearColor(0.1f, 0.1f, 0.1f, 1.0f));
	Border->SetPadding(2.0f);
	Border->SetContent(ClassPicker);

	return Border;
}

void SPKAssetPicker::OnClassSelectedFromPicker(UClass* Class)
{
	OnClassPicked.ExecuteIfBound(Class);
	ComboButton->SetIsOpen(false);
}

void SPKAssetPicker::SetContent( TSharedRef< SWidget > InContent )
{
	ContentContainer->SetContent(InContent);
}

const TSharedRef< SWidget >& SBorder::GetContent() const
{
	return ChildSlot.GetWidget();
}

void SPKAssetPicker::ClearContent()
{
	ChildSlot.DetachWidget();
}
