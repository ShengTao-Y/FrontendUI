// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widget_ConfirmScreen.generated.h"

class UCommonTextBlock;
class UDynamicEntryBox;
/**
 * 
 */
UCLASS(Abstract,BlueprintType,meta = (DisableNaiveTick))
class FRONTENDUI_API UWidget_ConfirmScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Title;

	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Message;

	//动态条目框，用于运行时动态添加按钮
	UPROPERTY(meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_Buttons;
	
};
