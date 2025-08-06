// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontendUI/Public/Controllers/FrontendPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AFrontendPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(),ACameraActor::StaticClass(),FName("Default"),FoundCameras);
	if(!FoundCameras.IsEmpty())
	{
		SetViewTarget(FoundCameras[0]);
	}
}
