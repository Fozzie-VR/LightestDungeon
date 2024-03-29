// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnSystem/LightestDungeonTurnController.h"
#include "LightestDungeon/LightestDungeonPlayerController.h"


// Sets default values
ALightestDungeonTurnController::ALightestDungeonTurnController()
{
	
}

// Called when the game starts or when spawned
void ALightestDungeonTurnController::BeginPlay()
{
	Super::BeginPlay();
	//get LightestDungeonPlayerController
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	ALightestDungeonPlayerController * LightestDungeonPlayerController = Cast<ALightestDungeonPlayerController>(playerController);
	//add callback
	LightestDungeonPlayerController->OnPlayerMove.AddDynamic(this, &ALightestDungeonTurnController::PlayerMovedCallback);
}

void ALightestDungeonTurnController:: PlayerMovedCallback()
{
	CurrentTurn++;
	const int TurnsRemaining = MaximumTurns - CurrentTurn;
	if(TurnsRemaining <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Over"));
		OnGameOver();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Turns Remaining: %d"), TurnsRemaining);
		OnTurnCounterChanged();
	}
}


