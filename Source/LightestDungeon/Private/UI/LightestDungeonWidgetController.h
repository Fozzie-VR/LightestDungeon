// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LightestDungeon/LightestDungeonPlayerController.h"
#include "UObject/Object.h"
#include "LightestDungeonWidgetController.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FControllerParams
{
	GENERATED_BODY()

	FControllerParams(){}

	FControllerParams(ALightestDungeonPlayerController* PC) : PlayerController(PC){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ALightestDungeonPlayerController> PlayerController = nullptr; 
	
};

UCLASS()
class LIGHTESTDUNGEON_API ULightestDungeonWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(FControllerParams Params);

	virtual void BroadcastInitialValues();

	virtual void BindCallbacksToDependencies();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<ALightestDungeonPlayerController> PlayerController;
	
};
