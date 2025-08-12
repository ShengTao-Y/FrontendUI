// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_ConfirmScreen.h"

#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "ICommonInputModule.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKScreen(const FText& InScreenTitle,
                                                                   const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Close;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("OK"));

	InfoObject->AvailableScreenButtons.Add(OKButtonInfo);
	return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle,
	const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo YesButtonInfo;
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	YesButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));

	FConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	NoButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("No"));

	InfoObject->AvailableScreenButtons.Add(YesButtonInfo);
	InfoObject->AvailableScreenButtons.Add(NoButtonInfo);
	return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKCancelScreen(const FText& InScreenTitle,
	const FText& InScreenMessage)
{
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("OK"));

	FConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Cancel"));

	InfoObject->AvailableScreenButtons.Add(OKButtonInfo);
	InfoObject->AvailableScreenButtons.Add(CancelButtonInfo);
	return InfoObject;
}

void UWidget_ConfirmScreen::InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject,
	TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
	check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);

	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);

	//如果条目框中的条目数量不等于0，就清除旧条目。（因为这个确认界面会创建多次，可能会残留之前的按钮）
	if(DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		//清空条目
		DynamicEntryBox_Buttons->Reset<UFrontendCommonButtonBase>(
			[](UFrontendCommonButtonBase& ExistingButton)
			{
				ExistingButton.OnClicked().Clear();
			}
		);
	}

	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty());

	//根据按钮信息，创建对应的按钮条目
	for(const FConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		FDataTableRowHandle InputActionRowHandle;
		switch (AvailableButtonInfo.ConfirmScreenButtonType)
		{
		case EConfirmScreenButtonType::Confirmed:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultClickAction();
			break;
			
		case EConfirmScreenButtonType::Cancelled:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
			
		case EConfirmScreenButtonType::Close:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		}
		UFrontendCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UFrontendCommonButtonBase>();
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		AddedButton->SetTriggeredInputAction(InputActionRowHandle);
		AddedButton->OnClicked().AddLambda(
		[ClickedButtonCallback,AvailableButtonInfo,this]()
			{
				ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);
				DeactivateWidget();//点击后停用控件
			}
		);
	}

	//对游戏手柄做的操作，让手柄的焦点聚集在最后一个按钮上
	if(DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
}
