// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/InputSettings.h"
#include "LightestDungeonPlayerController.generated.h"




/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class ALightestDungeonGrid;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerMove);


UCLASS()
class ALightestDungeonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALightestDungeonPlayerController();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerMove OnPlayerMove;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;
	

protected:

	UPROPERTY()
	ALightestDungeonGrid* Grid;

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	EHardwareDevicePrimaryType GetHardwareDevicePrimaryType() const;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	//Get cursor position to set grid selection box position
	void GetMousePosition(bool& IsValid, FVector& Location) const;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	FVector CachedDestination;
	FVector MousePosition;
	FVector SelectedTilePosition;

	bool bIsTouch; // Is it a touch device
	bool bIsOverGrid;
	float FollowTime; // For how long it has been pressed
};


