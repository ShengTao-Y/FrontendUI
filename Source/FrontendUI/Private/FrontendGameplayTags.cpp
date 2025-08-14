

#include "FrontendUI/Public/FrontendGameplayTags.h"

namespace FrontendGameplayTags
{
	//前端控件栈
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_Modal,"Frontend.WidgetStack.Modal");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_GameMenu,"Frontend.WidgetStack.GameMenu");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_GameHud,"Frontend.WidgetStack.GameHud");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_Frontend,"Frontend.WidgetStack.Frontend");

	//前端控件
	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_PressAnyKeyScreen,"Frontend.Widget.PressAnyKeyScreen");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_MainMenuScreen,"Frontend.Widget.MainMenuScreen");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_ConfirmScreen,"Frontend.Widget.OptionsScreen");
	
	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_OptionsScreen,"Frontend.Widget.ConfirmScreen");
}
