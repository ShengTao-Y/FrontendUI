// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"


void UListDataObject_Collection::AddChildListData(UListDataObject_Base* InChildListData)
{
	//子类初始化自身
	InChildListData->InitDataObject();

	//子类设置自己的父类
	InChildListData->SetParentData(this);

	ChildListDataArray.Add(InChildListData);
}

TArray<UListDataObject_Base*> UListDataObject_Collection::GetAllChildListData() const
{
	return ChildListDataArray;
}

bool UListDataObject_Collection::HasAnyChildListData() const
{
	return !ChildListDataArray.IsEmpty();
}
