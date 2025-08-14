// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widget_OptionScreen.generated.h"

/**
 * 
 */
UCLASS(Abstract,BlueprintType,meta = (DisableNaiveTick))
class FRONTENDUI_API UWidget_OptionScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

protected:
	//~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget Interface
private:	
	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();

	//重置当前选项的输入
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;
	//存储重置当前选项的输入句柄
	FUIActionBindingHandle ResetActionHandle;
};
