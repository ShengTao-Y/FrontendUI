﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ListDataObject_Base.generated.h"


#define LIST_DATA_ACCESSOR(DataType,PropertyName) \
FORCEINLINE DataType Get##PropertyName() const { return PropertyName;} \
void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName;}

UCLASS()
class FRONTENDUI_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()

	
public:
	LIST_DATA_ACCESSOR(FName,DataID)
	LIST_DATA_ACCESSOR(FText,DataDisplayName)
	LIST_DATA_ACCESSOR(FText,DescriptionRichText)
	LIST_DATA_ACCESSOR(FText,DisabledRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>,SoftDescriptionImage)
	LIST_DATA_ACCESSOR(UListDataObject_Base*,ParentData)

	//父类中是空的，子类重写这个函数
	virtual TArray<UListDataObject_Base*> GetChildSettingData() const { return TArray<UListDataObject_Base*>();}

private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	UListDataObject_Base* ParentData;
};
