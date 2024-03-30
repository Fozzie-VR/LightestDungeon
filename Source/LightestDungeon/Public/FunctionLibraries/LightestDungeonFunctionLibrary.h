// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LightestDungeonFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTESTDUNGEON_API ULightestDungeonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary|WidgetControllers")
	static UTurnWidgetController* GetTurnWidgetController(const UObject* WorldContextObject);
};
