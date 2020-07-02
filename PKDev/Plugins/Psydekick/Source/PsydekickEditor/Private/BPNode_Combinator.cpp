// Fill out your copyright notice in the Description page of Project Settings.


#include "BPNode_Combinator.h"
#include "PsydekickEditor.h"
#include "Psydekick/Public/PsydekickBPLibrary.h"
#include "Psydekick/Public/Data/ValueWrapper.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"

#include "K2Node_CallFunction.h"
#include "K2Node_MakeMap.h"
#include "K2Node_MakeArray.h"
#include "K2Node_GenericCreateObject.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_VariableSet.h"
#include "K2Node_Self.h"
#include "K2Node_MacroInstance.h"

#include "Kismet2/BlueprintEditorUtils.h"


//static const FName OuterPinName(TEXT("Outer"));
static const FName ClassPinName(TEXT("Class"));
//static const FName OutputPinName(TEXT("Output"));

void UBPNode_Combinator::AllocateDefaultPins()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	/*Create our pins*/

	// Execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	//Input
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Class, UObject::StaticClass(), ClassPinName);
//	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), OuterPinName);


	//Output
	UEdGraphPin* ResultPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), UEdGraphSchema_K2::PN_ReturnValue);
	ResultPin->PinType.ContainerType = EPinContainerType::Array;
}

FText UBPNode_Combinator::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Make Combinations");
}

FText UBPNode_Combinator::GetTooltipText() const
{
	return FText::FromString("Tooltip");
}

FText UBPNode_Combinator::GetMenuCategory() const
{
	return FText::FromString("PsydekickData");
}

void UBPNode_Combinator::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	UClass* Action = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(Action)) {
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		check(Spawner != nullptr);

		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}

void UBPNode_Combinator::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);

	UE_LOG(LogPsydekickEditor, Log, TEXT("PIN CONNECTION CHANGED %s %s"), *Pin->PinType.PinCategory.ToString(), *Pin->PinType.PinSubCategory.ToString());
	UEdGraphPin* OutputPin = FindPin(UEdGraphSchema_K2::PN_ReturnValue);
	for(auto& LinkedPin : Pin->LinkedTo)
	{

		UE_LOG(
			LogPsydekickEditor, Log, TEXT("\tLinked %s %s %s"),
			*LinkedPin->PinType.PinCategory.ToString(),
			*LinkedPin->PinType.PinSubCategory.ToString(),
			*LinkedPin->PinType.PinValueType.TerminalCategory.ToString()
		);
		TWeakObjectPtr<UObject> ObjPtr = LinkedPin->PinType.PinSubCategoryObject;
		if(ObjPtr.IsValid())
		{
			UE_LOG(LogPsydekickEditor, Log, TEXT("\tHave Obj %s"), *ObjPtr.Get()->GetClass()->GetName());
		}
	}
}

void UBPNode_Combinator::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	UE_LOG(LogPsydekickEditor, Log, TEXT("REALLOCATE"));
	AllocateDefaultPins();

	for(UEdGraphPin* OldPin : OldPins)
	{
		if(OldPin->GetName() == ClassPinName.ToString())
		{
			UE_LOG(LogPsydekickEditor, Log, TEXT("Found old class pin"));
			SetPinsForClass(Cast<UClass>(OldPin->DefaultObject));
		}
	}
}

void UBPNode_Combinator::PinDefaultValueChanged(UEdGraphPin* ChangedPin)
{
	UE_LOG(LogPsydekickEditor, Log, TEXT("PIN DEFAULT CHANGED %s %s"), *ChangedPin->PinType.PinCategory.ToString(), *ChangedPin->PinType.PinSubCategory.ToString());

	if(ChangedPin->GetName() == ClassPinName.ToString())
	{
		UE_LOG(LogPsydekickEditor, Log, TEXT("\tIt's the class pin"));
		SetPinsForClass(Cast<UClass>(ChangedPin->DefaultObject));
	}
}

void UBPNode_Combinator::SetPinsForClass(UClass* Class)
{
	if(Class)
	{
		UE_LOG(LogPsydekickEditor, Log, TEXT("Default: %s"), *Class->GetName());
		UEdGraphPin* OutputPin = FindPin(UEdGraphSchema_K2::PN_ReturnValue);
		OutputPin->PinType.PinSubCategoryObject = Class->GetAuthoritativeClass();

		const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

		for (TFieldIterator<UProperty> PropertyItr(Class); PropertyItr; ++PropertyItr)
		{
			UProperty* Property = *PropertyItr;
			UE_LOG(LogPsydekickEditor, Log, TEXT("Prop: %s"), *Property->GetName());

			FEdGraphPinType PropertyPinType;
			K2Schema->ConvertPropertyToPinType(Property, PropertyPinType);
			PropertyPinType.ContainerType = EPinContainerType::Array;

			UEdGraphPin* Pin = CreatePin(EGPD_Input, PropertyPinType, FName(*Property->GetName()));
		}
	}
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}

void UBPNode_Combinator::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UE_LOG(LogPsydekickEditor, Log, TEXT("Expanding node"));
	return;


	Super::ExpandNode(CompilerContext, SourceGraph);
	//static FName CreateCombinations_FunctionName = GET_FUNCTION_NAME_CHECKED(UPsydekickBPLibrary, MakeCombinations);
//	static FString Outer_ParamName = FString(TEXT("Outer"));
	static FString Class_ParamName = FString(TEXT("Class"));
	static FString Arrays_ParamName = FString(TEXT("Arrays"));

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Create BP Library function call node
	UFunction* BlueprintFunction =UPsydekickBPLibrary::StaticClass()->FindFunctionByName(FName(TEXT("MakeCombinationsOfObjects")));
	UK2Node_CallFunction* CallMakeCombosNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallMakeCombosNode->SetFromFunction(BlueprintFunction);
	CallMakeCombosNode->AllocateDefaultPins();

	// connect exec pin
	UEdGraphPin* ExternalPin;
	UEdGraphPin* InternalPin;

	// connect then pin
	UE_LOG(LogPsydekickEditor, Log, TEXT("Connecting THEN pin"));
	if(!HookupIntermediatePins(
		FindPinChecked(UEdGraphSchema_K2::PN_Then),
		CallMakeCombosNode->FindPinChecked(UEdGraphSchema_K2::PN_Then),
		TEXT("Then"),
		CompilerContext
	)) return;

	// connect Class pin
	if(!HookupIntermediatePins(
		FindPinChecked(ClassPinName),
		CallMakeCombosNode->FindPinChecked(Class_ParamName),
		TEXT("Class input"),
		CompilerContext
	)) return;

	// connect Outer/parent pin
//	if(!HookupIntermediatePins(
//		FindPinChecked(OuterPinName),
//		CallMakeCombosNode->FindPinChecked(Outer_ParamName),
//		TEXT("Outer input"),
//		CompilerContext
//	)) return;

	// connect output pin
	if(!HookupIntermediatePins(
		FindPinChecked(UEdGraphSchema_K2::PN_ReturnValue),
		CallMakeCombosNode->GetReturnValuePin(),
		TEXT("Output"),
		CompilerContext
	)) return;


	UK2Node_Self* SelfNode = CompilerContext.SpawnIntermediateNode<UK2Node_Self>(this, SourceGraph);
	SelfNode->AllocateDefaultPins();


	// make map node and connect
	UK2Node_MakeMap* MakeMapNode = CompilerContext.SpawnIntermediateNode<UK2Node_MakeMap>(this, SourceGraph);
	MakeMapNode->AllocateDefaultPins();
	if(!K2Schema->TryCreateConnection(MakeMapNode->GetOutputPin(), CallMakeCombosNode->FindPinChecked(Arrays_ParamName)))
	{
		CompilerContext.MessageLog.Error(TEXT("Failed to connect pin: MakeMapNode output to MakeCombos arrays input"), this);
		return;
	}

	FStringAssetReference ArrayWrapperAssetRef("/Script/Psydekick.ValueArrayWrapper");
	UScriptStruct* ArrayWrapperStruct = Cast<UScriptStruct>(ArrayWrapperAssetRef.TryLoad());

	UK2Node* LastNode = nullptr;
	UK2Node* FirstNode = nullptr;
	TArray<UEdGraphPin*> PropertyPins = GetPropertyPins();
	UE_LOG(LogPsydekickEditor, Log, TEXT("There are %d Property Pins"), PropertyPins.Num());
	for(UEdGraphPin* PropertyPin : PropertyPins)
	{
		UE_LOG(LogPsydekickEditor, Log, TEXT("Processing PropertyPin %s"), *PropertyPin->GetName());
		TArray<UEdGraphPin*> MapKeyPins;
		TArray<UEdGraphPin*> MapValuePins;
		// add input to map node
		if(LastNode)
		{
			UE_LOG(LogPsydekickEditor, Log, TEXT("Adding map input pin"));
			MakeMapNode->AddInputPin();
		}
		MakeMapNode->GetKeyAndValuePins(MapKeyPins, MapValuePins);

		// create a MakeArray node
		UK2Node_MakeArray* MakeArrayNode = CompilerContext.SpawnIntermediateNode<UK2Node_MakeArray>(this, SourceGraph);
		MakeArrayNode->AllocateDefaultPins();
		MapKeyPins.Last()->PinType.PinCategory = UEdGraphSchema_K2::PC_Name;
		K2Schema->TrySetDefaultValue(*MapKeyPins.Last(), PropertyPin->GetName());

		MapValuePins.Last()->PinType.PinSubCategoryObject = ArrayWrapperStruct;
		K2Schema->SplitPin(MapValuePins.Last());
		if(!K2Schema->TryCreateConnection(MakeArrayNode->GetOutputPin(), MapValuePins.Last()->SubPins[0]))
		{
			//FPinConnectionResponse Response = CompilerContext.MovePinLinksToIntermediate(*MakeArrayNode->GetOutputPin(), *MapValuePins.Last());
			FPinConnectionResponse Response = K2Schema->CanCreateConnection(MakeArrayNode->GetOutputPin(), MapValuePins.Last());
			if(!Response.CanSafeConnect() || Response.IsFatal()){
				CompilerContext.MessageLog.Error(TEXT("Failed to connect pin: MakeArray output to map value pins"), this);
				UE_LOG(LogPsydekickEditor, Error, TEXT("Failed to connect: %s"), *Response.Message.ToString());
				return;
			}
			else
			{
				UE_LOG(LogPsydekickEditor, Error, TEXT("maybe connect ?: %s"), *Response.Message.ToString());
			}
		}


		UK2Node_MacroInstance* ForEachNode = CompilerContext.SpawnIntermediateNode<UK2Node_MacroInstance>(this, SourceGraph);
		//MacroGraphReference=(
		//	MacroGraph=EdGraph'"/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:ForEachLoop"'
		//	GraphBlueprint=Blueprint'"/Engine/EditorBlueprintResources/StandardMacros.StandardMacros"',GraphGuid=99DBFD5540A796041F72A5A9DA655026)
		FStringAssetReference ForEachAssetRef("/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:ForEachLoop");
		UEdGraph* ForEachGraph = Cast<UEdGraph>(ForEachAssetRef.TryLoad());
		ForEachNode->SetMacroGraph(ForEachGraph);
		ForEachNode->AllocateDefaultPins();
		if(!FirstNode)
		{
			FirstNode = ForEachNode;
		}
		// @TODO: You are here, hooking up this ForEachNode
		/*
		ForEachNode->FindPin("Array")
		ForEachNode->FindPin("Array Element")
		*/
	/*
		if(!K2Schema->TryCreateConnection(, ))
		{
			CompilerContext.MessageLog.Error(TEXT("Failed to connect pin: Self to ConstructWrapper"), this);
			return;
		}
	*/


		// add items to that make array node
		//MakeArrayNode->AddInputPin();

		// construct wrapper
		UK2Node_GenericCreateObject* ConstructWrapper = CompilerContext.SpawnIntermediateNode<UK2Node_GenericCreateObject>(this, SourceGraph);
		ConstructWrapper->AllocateDefaultPins();
		ConstructWrapper->GetClassPin()->DefaultObject = UBooleanWrapper::StaticClass();
		ConstructWrapper->GetClassPin()->PinType.PinSubCategoryObject = UBooleanWrapper::StaticClass();
		ConstructWrapper->ReconstructNode();
		if(!K2Schema->TryCreateConnection(SelfNode->Pins[0], ConstructWrapper->GetOuterPin()))
		{
			CompilerContext.MessageLog.Error(TEXT("Failed to connect pin: Self to ConstructWrapper"), this);
			return;
		}


		if(!K2Schema->TryCreateConnection(ConstructWrapper->GetResultPin(), MakeArrayNode->Pins.Last()))
		{
			CompilerContext.MessageLog.Error(TEXT("Failed to connect pin: Construct ValueWrapper to MakeArray"), this);
			FPinConnectionResponse Response = K2Schema->CanCreateConnection(
				MakeArrayNode->Pins.Last(),
				ConstructWrapper->GetResultPin()
			);
			UE_LOG(LogPsydekickEditor, Error, TEXT("\tFailed to connect: %s"), *Response.Message.ToString());
			return;
		}




		// set value on wrapper

		UK2Node_VariableSet* ValueSetter = CompilerContext.SpawnIntermediateNode<UK2Node_VariableSet>(this, SourceGraph);
		ValueSetter->AllocateDefaultPins();
		ValueSetter->SetFromProperty(
			UBooleanWrapper::StaticClass()->FindPropertyByName(FName("Value")), false, UBooleanWrapper::StaticClass()
		);
		ValueSetter->ReconstructNode();

		ConstructWrapper->GetResultPin()->PinType.PinSubCategoryObject = ValueSetter->FindPin(FName("self"))->PinType.PinSubCategoryObject;
		UE_LOG(LogPsydekickEditor, Log, TEXT("Hooking up value setter pin: %s"), *ValueSetter->FindPin(FName("self"))->PinToolTip);
		if(!K2Schema->TryCreateConnection(ConstructWrapper->GetResultPin(), ValueSetter->FindPin(FName("self"))))
		{
			CompilerContext.MessageLog.Error(TEXT("Failed to connect pin: Construct result to setter target"), this);
			return;
		}

		UE_LOG(LogPsydekickEditor, Log, TEXT("Hooking up execs"));
		if(LastNode != nullptr){
			HookupThenToExec(LastNode, ForEachNode, K2Schema);
		}
		K2Schema->TryCreateConnection(ForEachNode->FindPinChecked(FName("LoopBody")), ConstructWrapper->GetExecPin());
		HookupThenToExec(ConstructWrapper, ValueSetter, K2Schema);

		LastNode = ForEachNode;
	}


	UE_LOG(LogPsydekickEditor, Log, TEXT("Done with property pins"));
	if(FirstNode && LastNode)
	{
		if(!HookupIntermediatePins(GetExecPin(), FirstNode->GetExecPin(), "Execute", CompilerContext))
		{
			return;
		}
		HookupThenToExec(LastNode, CallMakeCombosNode, K2Schema);
	}
	else
	{
		UE_LOG(LogPsydekickEditor, Warning, TEXT("No intermediate nodes!"));
		if(!HookupIntermediatePins(GetExecPin(), CallMakeCombosNode->GetExecPin(), "Execute", CompilerContext))
		{
			return;
		}
	}

	//FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint())
	//K2Schema->DuplicateGraph()

	// connect to called function Arrays pin
	//	For each array pin
	//		for each item in array
	//			add an input pin to the MakeArray node
	//

	//  Blueprint'/Engine/EditorBlueprintResources/StandardMacros.StandardMacros'

	/*
		UK2Node_MakeArray* MakeArrayNode = SpawnIntermediateNode<UK2Node_MakeArray>(MacroInstanceNode, SourceGraph);
		MakeArrayNode->NumInputs = 0; // the generated array should be empty
		MakeArrayNode->AllocateDefaultPins();
	*/

	BreakAllNodeLinks();
}

TArray<UEdGraphPin*> UBPNode_Combinator::GetPropertyPins()
{
	TArray<UEdGraphPin*> PropertyPins;
	TArray<UEdGraphPin*> NonPropertyPins;
	NonPropertyPins.Emplace(GetExecPin());
	NonPropertyPins.Emplace(FindPinChecked(UEdGraphSchema_K2::PN_Then));
	NonPropertyPins.Emplace(FindPinChecked(ClassPinName));
//	NonPropertyPins.Emplace(FindPinChecked(OuterPinName));
	NonPropertyPins.Emplace(FindPinChecked(UEdGraphSchema_K2::PN_ReturnValue));

	for(UEdGraphPin* Pin : Pins)
	{
		if(!NonPropertyPins.Contains(Pin))
		{
			PropertyPins.Add(Pin);
		}
	}

	return PropertyPins;
}

bool UBPNode_Combinator::HookupIntermediatePins(UEdGraphPin* ExternalPin, UEdGraphPin* InternalPin, FString Name, class FKismetCompilerContext& CompilerContext)
{
	if(ExternalPin == nullptr || InternalPin == nullptr)
	{
		UE_LOG(LogPsydekickEditor, Warning, TEXT("BPNode_Combinator::ExpandNode could not find %s pin for intermediate hookup"), *Name);
		CompilerContext.MessageLog.Error(TEXT("Could not find pin for internal hookup. Try refreshing the node?"), this);
		return false;
	}

	FPinConnectionResponse Response = CompilerContext.MovePinLinksToIntermediate(*ExternalPin, *InternalPin);
	if(!Response.CanSafeConnect() || Response.IsFatal()){
		UE_LOG(LogPsydekickEditor, Error, TEXT("Failed to connect %s: %s"), *Name, *Response.Message.ToString())
		return false;
	}

	return true;
}

void UBPNode_Combinator::HookupThenToExec(UK2Node* A, UK2Node* B, const UEdGraphSchema_K2* K2Schema)
{
	UEdGraphPin* ThenPin = A->FindPinChecked(UEdGraphSchema_K2::PN_Then);
	if(!ThenPin)
	{
		ThenPin = A->FindPinChecked(FName("Completed"));
	}
	K2Schema->TryCreateConnection(ThenPin, B->GetExecPin());
}


void UBPNode_Combinator::MakeArray(TSubclassOf<UObject> Class)
{
	TArray<Class>
}