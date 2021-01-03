// Fill out your copyright notice in the Description page of Project Settings.


#include "2D/MenuTreeWidget.h"

void UMenuTreeWidget::Show_Implementation()
{
	AddToViewport();
}

void UMenuTreeWidget::Hide_Implementation()
{
	RemoveFromParent();
}
