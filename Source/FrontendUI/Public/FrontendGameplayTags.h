#pragma once

#include "NativeGameplayTags.h"

namespace FrontendGameplayTags
{
	 //添加这个FRONTENDUI_API后，可以在其他的模块中访问FrontendGameplayTags
	/*
	* 使用C++定义标签。 你可以使用 NativeGameplayTags.h 中定义的以下宏，通过C++来定义Gameplay标签：
	* 1、UE_DECLARE_GAMEPLAY_TAG_EXTERN ：在头文件中用于声明cpp文件中定义的标签。
	* 2、UE_DEFINE_GAMEPLAY_TAG ：在cpp文件中用于定义头文件中声明的标签，不带提示文本注释。
	* 3、UE_DEFINE_GAMEPLAY_TAG_COMMENT ：在cpp文件中用于定义头文件中声明的标签，带有提示文本注释。
	* 
	* 4、UE_DEFINE_GAMEPLAY_TAG_STATIC ：在 cpp 文件中用于定义仅对定义文件可用的标签。不同于其他 DEFINE 宏，这不应该与 DECLARE 宏调用配对。
	 */
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Modal);
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameMenu);
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameHud);
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Frontend);
}

