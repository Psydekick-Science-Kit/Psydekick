// Fill out your copyright notice in the Description page of Project Settings.


#include "2D/MenuTreeWidget.h"

void UMenuTreeWidget::AnimateIn()
{
	if(IsValid(OutAnimation))
	{
		UnbindFromAnimationFinished(OutAnimation, AnimateOutFinished);
	}

	if(IsValid(InAnimation))
	{
		PlayAnimationForward(InAnimation, 1.0f, false);
	}
}

void UMenuTreeWidget::AnimateOut()
{
	if(IsValid(OutAnimation))
	{
		BindToAnimationFinished(OutAnimation, AnimateOutFinished);
		PlayAnimationForward(OutAnimation, 1.0f, false);
	}
	else
	{
		AnimateOutFinished.ExecuteIfBound();
	}

}
