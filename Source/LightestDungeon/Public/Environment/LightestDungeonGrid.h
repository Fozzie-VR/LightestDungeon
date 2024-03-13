// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Util/ColorConstants.h"
#include "LightestDungeonGrid.generated.h"


UCLASS()
class LIGHTESTDUNGEON_API ALightestDungeonGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightestDungeonGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProceduralMeshComponent* GridMesh;

private:

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	int32 NumRows;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
                     	int32 NumColumns;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	float TileSize;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	float LineThickness;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	FLinearColor LineColor;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	FLinearColor SelectionColor;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	float LineOpacity;
	
	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	float SelectionOpacity;

	
	
	
};
