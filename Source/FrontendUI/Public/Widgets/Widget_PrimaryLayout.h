// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Widget_PrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;

  /*
  * Abstract指定此类为抽象基类。可被继承，但不可生成对象。
  * BlueprintType 可当做变量类型
  * DisableNaiveTick 禁用该UserWidget的NativeTick
  */
UCLASS(Abstract,BlueprintType,meta = (DisableNaiveTick))
class FRONTENDUI_API UWidget_PrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag& InTag) const;

protected:
	//UPARAM(meta = (Categories = "Frontend.WidgetStack"))用来过滤FGameplayTag的类型
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetStack(UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InStackTag,UCommonActivatableWidgetContainerBase* InStack);

private:
	//Transient 不序列化该属性，该属性初始化时候会被0填充
	UPROPERTY(Transient)
	TMap<FGameplayTag,UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
	
};
