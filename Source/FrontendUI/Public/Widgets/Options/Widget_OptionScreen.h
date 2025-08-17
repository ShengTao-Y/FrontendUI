// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widget_OptionScreen.generated.h"

class UOptionsDataRegistry;
class UFrontendCommonTabListWidgetBase;

UCLASS(Abstract,BlueprintType,meta = (DisableNaiveTick))
class FRONTENDUI_API UWidget_OptionScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

protected:
	//~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget Interface

	//~ Begin UCommonActivatableWidget Interface
	virtual void NativeOnActivated() override;
	//~ End UCommonActivatableWidget Interface
	
private:
	
	UOptionsDataRegistry* GetOrCreateDataRegistry();

	UFUNCTION()
	void OnOptionsTabSelected(FName TabId);
	
	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UFrontendCommonTabListWidgetBase* TabListWidget_OptionsTabs;
	//***** Bound Widgets ***** //
	
	//在选项屏幕中处理数据的创建。禁止直接访问该变量
	UPROPERTY(Transient)
	UOptionsDataRegistry* CreatedOwningDataRegistry;//这个数据在DeActive时可能会被删除

	//重置当前选项的输入
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;
	//存储重置当前选项的输入句柄
	FUIActionBindingHandle ResetActionHandle;
};
