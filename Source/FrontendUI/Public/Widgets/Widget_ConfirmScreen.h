// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FrontendTypes/FrontendEnumTypes.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widget_ConfirmScreen.generated.h"

USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unknown;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText ButtonTextToDisplay;
};

UCLASS(Abstract,BlueprintType,meta = (DisableNaiveTick))
class FRONTENDUI_API UConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:
	//用来创建"OK"的UI界面
	static UConfirmScreenInfoObject* CreateOKScreen(const FText& InScreenTitle,const FText& InScreenMessage);
	//用来创建"Yes/No"的UI界面
	static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle,const FText& InScreenMessage);
	//用来创建"OK/Cancel"的UI界面
	static UConfirmScreenInfoObject* CreateOKCancelScreen(const FText& InScreenTitle,const FText& InScreenMessage);

	
	UPROPERTY(Transient)
	FText ScreenTitle;
	
	UPROPERTY(Transient)
	FText ScreenMessage;

	//根据这个数组就可以知道需要添加几个按钮
	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;
	
};

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
