// Fill out your copyright notice in the Description page of Project Settings.


#include "Flow/StimulusConfiguration.h"

#include "Psydekick.h"

FString UStimulusConfiguration::ToString_Implementation()
{
	FString PropValues = "";

	for (TFieldIterator<FProperty> PropertyIterator(GetClass()); PropertyIterator; ++PropertyIterator)
	{
		TFieldPath<FProperty> Property = *PropertyIterator;
		PropValues += Property->GetName() + "=";

		if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(*Property))
		{
			PropValues += BoolProperty->GetPropertyValue_InContainer(this) ? "true" : "false";
		}
		else if (FIntProperty* IntProperty = CastField<FIntProperty>(*Property))
		{
			PropValues.AppendInt(IntProperty->GetPropertyValue_InContainer(this));
		}
		else if (FFloatProperty* FloatProperty = CastField<FFloatProperty>(*Property))
		{
			FString::SanitizeFloat(FloatProperty->GetPropertyValue_InContainer(this));
		}
		else if (FStrProperty* StringProperty = CastField<FStrProperty>(*Property))
		{
			PropValues += StringProperty->GetPropertyValue_InContainer(this);
		}
		else if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(*Property))
		{
			PropValues += "<Object>";
		}
		else {
			PropValues += "?";
		}

		PropValues += ",";
	}

	if (PropValues.Len() > 0)
	{
		return GetName() + "(" + PropValues.Mid(0, PropValues.Len() - 1) + ")";
	}
	else {
		return GetName() + "()";
	}

}
