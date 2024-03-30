// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LightestDungeonWidgetController.h"
#include "TurnWidgetController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrentTurnChangedSignature);

UCLASS(BlueprintType, Blueprintable)
class LIGHTESTDUNGEON_API UTurnWidgetController : public ULightestDungeonWidgetController
{
	GENERATED_BODY()

public :

	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	

	UPROPERTY(BlueprintReadOnly, Category = "Turn Properties")
	int32 CurrentTurn = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Properties")
	int32 MaxTurns = 10;

	UPROPERTY(BlueprintAssignable, Category = "Turn Events")
	FOnCurrentTurnChangedSignature OnCurrentTurnChanged;

private:
	UFUNCTION()
	void SetCurrentTurn();

	UFUNCTION(BlueprintCallable)
	int32 GetTurnsLeft() const;
};
