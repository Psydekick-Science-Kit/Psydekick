// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "AssetData.h"

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "PropertyCustomizationHelpers.h"
#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"

DECLARE_DELEGATE_OneParam(FClassPicked, UClass*);

class FCustomClassViewerFilter : public IClassViewerFilter
{
public:
	TSet <const UClass*> AllowedChildrenOfClasses;

	EClassFlags DisallowedClassFlags;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		return !InClass->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};

class PSYDEKICKED_API SPKAssetPicker : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPKAssetPicker)
	{}
		SLATE_EVENT( FClassPicked, OnClassPicked )
		SLATE_DEFAULT_SLOT( FArguments, Content )
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/**
	 * Sets the content for this border
	 *
	 * @param	InContent	The widget to use as content for the border
	 */
	virtual void SetContent( TSharedRef< SWidget > InContent );

	/**
	 * Gets the content for this border
	 *
	 * @return The widget used as content for the border
	 */
	const TSharedRef< SWidget >& GetContent() const;

	/** Clears out the content for the border */
	void ClearContent();

	FClassPicked OnClassPicked;


protected:
	TSharedPtr<SComboButton> ComboButton;
	TSharedPtr<SBorder> ContentContainer;
	TSharedRef<SWidget> GetClassPicker();

	TSharedPtr<FCustomClassViewerFilter> Filter;

private:

	void OnAssetSelectedFromPicker(const struct FAssetData& AssetData);
	void OnClassSelectedFromPicker(UClass* Class);
};
