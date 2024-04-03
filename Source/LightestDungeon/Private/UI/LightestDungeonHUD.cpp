// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LightestDungeonHUD.h"
#include "Blueprint/UserWidget.h"
#include "LightestDungeonWidgetController.h"
#include "TurnSystem/TurnWidgetController.h"
#include "UI/LightestDungeonUserWidget.h"


void ALightestDungeonHUD::InitializeOverlay(ALightestDungeonPlayerController* PlayerController)
{
	OverlayWidget =  CreateWidget<ULightestDungeonUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();

	FControllerParams Params(PlayerController);
	GetTurnWidgetController(Params);
	
}

UTurnWidgetController* ALightestDungeonHUD::GetTurnWidgetController(const FControllerParams& Params)
{
	if(TurnWidgetController == nullptr)
	{
		TurnWidgetController = NewObject<UTurnWidgetController>(this, TurnWidgetControllerClass);
		TurnWidgetController->SetWidgetControllerParams(Params);
		TurnWidgetController->BindCallbacksToDependencies();
	}
	return TurnWidgetController;
}
