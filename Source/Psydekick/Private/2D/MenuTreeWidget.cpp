// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "2D/MenuTreeWidget.h"

void UMenuTreeWidget::Show_Implementation()
{
	AddToViewport();
}

void UMenuTreeWidget::Hide_Implementation()
{
	RemoveFromParent();
}
