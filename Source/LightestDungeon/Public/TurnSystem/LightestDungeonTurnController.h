// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightestDungeonTurnController.generated.h"

UCLASS()
class LIGHTESTDUNGEON_API ALightestDungeonTurnController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALightestDungeonTurnController();
	
	UPROPERTY(BlueprintReadOnly, Category = "Turn Counter")
	int32 CurrentTurn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turn Counter")
	int32 MaximumTurns;

	UFUNCTION(BlueprintImplementableEvent)
	void OnTurnCounterChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameOver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void PlayerMovedCallback();
	
};