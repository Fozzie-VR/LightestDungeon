// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/LightestDungeonFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/LightestDungeonHUD.h"
#include "UI/LightestDungeonWidgetController.h"


UTurnWidgetController* ULightestDungeonFunctionLibrary::GetTurnWidgetController(const UObject* WorldContextObject)
{
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(ALightestDungeonHUD* LightestDungeonHUD = Cast<ALightestDungeonHUD>(PC->GetHUD()))
		{
			ALightestDungeonPlayerController * PlayerController = Cast<ALightestDungeonPlayerController>(PC);
			const FControllerParams Params(PlayerController);
			return LightestDungeonHUD->GetTurnWidgetController(Params);
		}
	}
	return nullptr;
}
