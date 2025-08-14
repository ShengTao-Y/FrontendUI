// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/Widget_OptionScreen.h"
#include "FrontentDebugHelper.h"
#include "ICommonInputModule.h"
#include "Input/CommonUIInputTypes.h"

void UWidget_OptionScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)
			)
		);
	}
	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this,&ThisClass::OnBackBoundActionTriggered)
		)
	);
	
}
void UWidget_OptionScreen::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("Reset bound action triggered"));
}
void UWidget_OptionScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}
