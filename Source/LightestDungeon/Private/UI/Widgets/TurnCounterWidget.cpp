// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/TurnCounterWidget.h"

#include "Components/TextBlock.h"
#include "FunctionLibraries/LightestDungeonFunctionLibrary.h"
#include "TurnSystem/TurnWidgetController.h"
//#include "TurnCounterWidget.generated.h"


void UTurnCounterWidget::SetTurnWidgetController()
{
	TurnWidgetController = ULightestDungeonFunctionLibrary::GetTurnWidgetController(this);
	TurnWidgetController->OnTurnsLeftChanged.AddUObject(this, &UTurnCounterWidget::TurnsLeftChangedCallback);
}

void UTurnCounterWidget::TurnsLeftChangedCallback(int CurrentTurn)
{
	//update widget
	if(TurnsRemainingTextBlock != nullptr)
	{
		TurnsRemainingTextBlock->SetText(FText::AsNumber(CurrentTurn));
	}
}
