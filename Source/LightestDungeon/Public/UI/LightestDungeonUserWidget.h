// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LightestDungeonUserWidget.generated.h"

/**
 * 
 */

class ULightestDungeonWidgetController;
UCLASS()
class LIGHTESTDUNGEON_API ULightestDungeonUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(ULightestDungeonWidgetController* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ULightestDungeonWidgetController> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
