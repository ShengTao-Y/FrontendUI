// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/FrontendUISubsystem.h"

#include "FrontendBlueprintFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_ConfirmScreen.h"

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

void UFrontendUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag,
	TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
	TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AysncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	/*单个文件异步加载*/
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			//匿名函数。要在匿名函数中使用不在其父函数体之内的变量，只能通过this传递。
			[InSoftWidgetClass,this,InWidgetStackTag,AysncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
				
				check(LoadedWidgetClass && CreatedPrimaryLayout);

				//在RegisteredWidgetStackMap中查找对应标签的控件栈
				UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);

				//生成（创建或从非活动池中提取）给定小部件类的实例并将其添加到容器中。【创建实例且添加到容器中时就是添加到视口了】
				UWidget_ActivatableBase* CreatedWidget = FoundWidgetStack->AddWidget<UWidget_ActivatableBase>(
					LoadedWidgetClass,
					//匿名函数，在实例生成之后，在实际添加到容器之前被调用。
					[AysncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
					{
						//TFunction函数
						AysncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush,&CreatedWidgetInstance);
					}
				);

				AysncPushStateCallback(EAsyncPushWidgetState::AfterPush,CreatedWidget);
			}
		)
	);
}

void UFrontendUISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType,
	const FText& InScreenTitile, const FText& InScreenMsg,
	TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	UConfirmScreenInfoObject* CreateInfoObject = nullptr;
	switch (InScreenType)
	{
	case EConfirmScreenType::OK:
		CreateInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitile,InScreenMsg);
		break;

	case EConfirmScreenType::YesNo:
		CreateInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitile,InScreenMsg);
		break;
	
	case EConfirmScreenType::OkCancel:
		CreateInfoObject = UConfirmScreenInfoObject::CreateOKCancelScreen(InScreenTitile,InScreenMsg);
		break;

	case EConfirmScreenType::Unknown:
		break;
	default:
		break;
	}

	check(CreateInfoObject);

	PushSoftWidgetToStackAsync(
		FrontendGameplayTags::Frontend_WidgetStack_Modal,
		UFrontendBlueprintFunctionLibrary::GetFrontendSoftWidgetClassesByTag(FrontendGameplayTags::Frontend_Widget_ConfirmScreen),
		[CreateInfoObject,ButtonClickedCallback](EAsyncPushWidgetState InPushState,UWidget_ActivatableBase* PushedWidget)
		{
			if(InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreateInfoObject,ButtonClickedCallback);
			}
		}
	);
}
