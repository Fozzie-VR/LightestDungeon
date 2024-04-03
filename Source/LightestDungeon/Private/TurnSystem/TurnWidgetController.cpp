// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnSystem/TurnWidgetController.h"

void UTurnWidgetController::BindCallbacksToDependencies()
{
	PlayerController->OnPlayerMove.AddDynamic(this, &UTurnWidgetController::SetCurrentTurn);
}

void UTurnWidgetController::BroadcastInitialValues()
{
	OnTurnsLeftChanged.Broadcast(MaxTurns);
}

void UTurnWidgetController::SetCurrentTurn()
{
	CurrentTurn++;
	OnTurnsLeftChanged.Broadcast(GetTurnsLeft());
}

int32 UTurnWidgetController::GetTurnsLeft() const
{
	return   MaxTurns - CurrentTurn;
}
