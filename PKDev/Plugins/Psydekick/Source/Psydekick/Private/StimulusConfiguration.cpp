// Fill out your copyright notice in the Description page of Project Settings.


#include "StimulusConfiguration.h"

#include "Psydekick.h"

FString UStimulusConfiguration::ToString_Implementation()
{
	FString PropValues = "";

	for (TFieldIterator<UProperty> PropertyIterator(GetClass()); PropertyIterator; ++PropertyIterator)
	{
		UProperty* Property = *PropertyIterator;
		PropValues += Property->GetName() + "=";

		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(Property))
		{
			PropValues += BoolProperty->GetPropertyValue_InContainer(this) ? "true" : "false";
		}
		else if (UIntProperty* IntProperty = Cast<UIntProperty>(Property))
		{
			PropValues.AppendInt(IntProperty->GetPropertyValue_InContainer(this));
		}
		else if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(Property))
		{
			FString::SanitizeFloat(FloatProperty->GetPropertyValue_InContainer(this));
		}
		else if (UStrProperty* StringProperty = Cast<UStrProperty>(Property))
		{
			PropValues += StringProperty->GetPropertyValue_InContainer(this);
		}
		else if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
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
