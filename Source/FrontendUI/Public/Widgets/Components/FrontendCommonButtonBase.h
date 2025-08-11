// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "FrontendCommonButtonBase.generated.h"

class UCommonTextBlock;

UCLASS(Abstract,BlueprintType,meta = (DisableNaiveTick))
class FRONTENDUI_API UFrontendCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	void SetButtonText(FText InText);

private:
	//--- Begin UUSerWidget Interface ---//
	virtual void NativePreConstruct() override;
	//--- End UUSerWidget Interface ---//

	//--- Begin UCommonButtonBase Interface ---//
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	//--- End UCommonButtonBase Interface ---//

	//**** Bound Widgets ****//
	UPROPERTY(meta = (BindWidgetOptional))
	UCommonTextBlock* CommonTextBlock_ButtonText;
	//**** Bound Widgets ****//

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Frontend Button",meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;

	//文本是否使用大写
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Frontend Button",meta = (AllowPrivateAccess = "true"))
	bool bUserUpperCaseForButtonText = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Frontend Button",meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;
	
};
