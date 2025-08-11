// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "FrontendDeveloperSettings.generated.h"

class UWidget_ActivatableBase;
/**
 * Config = Game表示这个设置在“项目设置”中会出现在“Game”类别下,数据会写入本地的“DefaultGame.ini”文件中
 */
UCLASS(Config = Game,DefaultConfig,meta = (DisplayName = "Frontend UI Settings"))
class FRONTENDUI_API UFrontendDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	//FrorceInlineRow表示将键值强制放到同一行
	UPROPERTY(Config,EditAnywhere,Category = "Widget Reference",meta = (FrorceInlineRow,Categories = "Frontend.Widget"))
	TMap< FGameplayTag,TSoftClassPtr<UWidget_ActivatableBase> > FrontendWidgetMap;
	
};
