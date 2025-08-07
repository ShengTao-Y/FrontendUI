// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_PushSoftWidget.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(
	const UObject* WorldContextObject,
	APlayerController* OwningPlayerController,
	TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
	FGameplayTag InWidgetStackTag,
	bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(),TEXT("PushSoftWidgetToStack was passed a null soft widget class "));

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();

			/*
			 * 调用全局注册这个对象到一个游戏实例，它不会被销毁，直到SetReadyToDestroy被调用
			 * 这允许有一个动作保持活跃，直到SetReadyToDestroy被手动调用。允许在循环中使用，或者调用的蓝图消失
			 */
			Node->RegisterWithGameInstance(World);
			return Node;
		}
	}

	return nullptr;
}
