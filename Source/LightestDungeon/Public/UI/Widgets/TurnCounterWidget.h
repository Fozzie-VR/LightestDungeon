// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LightestDungeonUserWidget.h"
#include "TurnCounterWidget.Generated.h"
/**
 * 
 */
class UTurnWidgetController;
UCLASS()
class LIGHTESTDUNGEON_API UTurnCounterWidget : public ULightestDungeonUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UTurnWidgetController> TurnWidgetController;

	UFUNCTION(BlueprintCallable)
	void SetTurnWidgetController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TurnsRemainingTextBlock = nullptr;

	UFUNCTION()
	void TurnsLeftChangedCallback(int CurrentTurn);

};
