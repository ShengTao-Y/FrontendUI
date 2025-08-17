// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Components/FrontendCommonTabListWidgetBase.h"

#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"

void UFrontendCommonTabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName)
{
}

#if WITH_EDITOR
void UFrontendCommonTabListWidgetBase::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);
	
	if (!TabButtonEntryWidgetClass)
	{
		CompileLog.Error(FText::FromString(
			TEXT("The variable TabButtonEntryWidgetClass has no valid entry specified. ") +
			GetClass()->GetName() + 
			TEXT(" needs a valid entry widget class to function properly")
		));
	}
}
#endif