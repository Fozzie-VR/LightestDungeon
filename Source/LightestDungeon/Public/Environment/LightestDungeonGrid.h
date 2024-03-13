// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Util/ColorConstants.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "LightestDungeonGrid.generated.h"


UCLASS()
class LIGHTESTDUNGEON_API ALightestDungeonGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightestDungeonGrid();

	UFUNCTION()
	void LocationToTile(FVector Location, bool IsValid, int32 &Row, int32 &Column);

	UFUNCTION()
	void TileToLocation(int32 Row, int32 Column, bool IsCenter, bool &IsValid, FVector2D &Location);

	UFUNCTION()
	void SetSelectedTile(int32 Row, int32 Column);

	UFUNCTION()
	bool IsTileValid(int32 Row, int32 Column) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProceduralMeshComponent* GridMesh;

private:

	UFUNCTION()
	void DrawLine(FVector Start, FVector End, float LineThickness, TArray<FVector> &Vertices, TArray<int32> &Triangles);

	UFUNCTION()
	void DrawHorizontalLines();

	UFUNCTION()
	void DrawVerticalLines();

	UFUNCTION(BlueprintPure)
	float GetWidth() const;

	UFUNCTION(BlueprintPure)
	float GetHeight() const;

	UFUNCTION()
	UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor Color, float Opacity);

	UPROPERTY()
	UMaterialInstanceDynamic* LineMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* SelectionMaterialInstance;
	
	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	UMaterialInterface *ParentMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	int32 NumRows = 10;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	int32 NumColumns = 10;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	float TileSize = 100;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	float LineThickness = 10;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	FLinearColor LineColor;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	FLinearColor SelectionColor;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	float LineOpacity;
	
	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	float SelectionOpacity;
	
};
