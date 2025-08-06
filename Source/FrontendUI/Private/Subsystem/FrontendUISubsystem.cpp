// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/FrontendUISubsystem.h"

UFrontendUISubsystem* UFrontendUISubsystem::Get(const UObject* WorldContextObject)
{
	if(GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::Assert);
		return UGameInstance::GetSubsystem<UFrontendUISubsystem>(World->GetGameInstance());
	}
	return nullptr;
}

bool UFrontendUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if(!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance()) //这个类的实例不在专属服务器上
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(),FoundClasses);//返回指定父类的子类的数组

		return FoundClasses.IsEmpty();//当有不同的子类继承自这个类时，父类将不会被创建
	}
	return false;
}

void UFrontendUISubsystem::RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreateWidget)
{
	check(InCreateWidget);
	
	CreatedPrimaryLayout = InCreateWidget;
}
