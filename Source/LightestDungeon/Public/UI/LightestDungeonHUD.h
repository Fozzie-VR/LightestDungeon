// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LightestDungeonHUD.generated.h"


class UTurnWidgetController;
class ALightestDungeonPlayerController;
struct FControllerParams;
/**
 * 
 */
class ULightestDungeonUserWidget;
UCLASS()
class LIGHTESTDUNGEON_API ALightestDungeonHUD : public AHUD
{
	GENERATED_BODY()

public:

	void InitializeOverlay(ALightestDungeonPlayerController *PlayerController);

	UTurnWidgetController* GetTurnWidgetController(const FControllerParams& Params);

private:

	UPROPERTY()
	TObjectPtr<ULightestDungeonUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ULightestDungeonUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UTurnWidgetController> TurnWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTurnWidgetController> TurnWidgetControllerClass;
	
	
};
