// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "K2Node.h"
#include "K2Node_MakeContainer.h"

#include "BPNode_Combinator.generated.h"

/**
 *
 */
UCLASS()
class PSYDEKICKEDITOR_API UBPNode_Combinator : public UK2Node
{
	GENERATED_BODY()

public:
	//~ Begin UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	//~ End UEdGraphNode Interface

	//~ Begin UK2Node Interface
	virtual FText GetMenuCategory() const override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	//~ End UK2Node Interface

	void SetPinsForClass(UClass* Class);
	bool HookupIntermediatePins(UEdGraphPin* ExternalPin, UEdGraphPin* InternalPin, FString Name, class FKismetCompilerContext& CompilerContext);
	void HookupThenToExec(UK2Node* A, UK2Node* B, const UEdGraphSchema_K2* K2Schema);

protected:
	//UEdGraphPin* InClassPin;
	//UEdGraphPin* OutputPin;

	TArray<UEdGraphPin*> GetPropertyPins();

	UFUNCTION(BlueprintCallable)
	void MakeArray(TSubclassOf<UObject> Class);
};
