// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "LightestDungeonGrid.generated.h"

USTRUCT()
struct FTileCoords
{
	GENERATED_BODY()

	int32 Row = 0;
	int32 Column = 0;

	FTileCoords(){}

	FTileCoords(int32 TileRow, int32 TileColumn)
	{
		Row = TileRow;
		Column = TileColumn;
	}
};


UCLASS(BlueprintType, Blueprintable)
class LIGHTESTDUNGEON_API ALightestDungeonGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightestDungeonGrid();

    FTileCoords CurrentTile {0,0};

	
	TArray<FTileCoords> GetTilesInPlayerRange(int Range) const;

	UPROPERTY()
	TArray<int> OutlineMeshIndices;

	UFUNCTION()
	void OutlineReachableTiles();

	UFUNCTION()
	void SetPlayerRange(int Range);
	

	UFUNCTION()
	void LocationToTile(FVector Location, bool& IsValid, int32 &Row, int32 &Column) const;

	UFUNCTION()
	void TileToLocation(int32 Row, int32 Column, FVector &Location, FVector &Center) const;

	UFUNCTION()
	FVector GetOutlineVertex(int32 Row, int32 Column) const;
	
	UFUNCTION()
	void SetSelectedTile(int32 Row, int32 Column);

	UFUNCTION()
	bool IsTileValid(int32 Row, int32 Column) const;

	void UpdateSelectionBoxPosition(FVector CursorPosition, bool& CursorOverGrid);

	FVector GetSelectionBoxCenter() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProceduralMeshComponent* GridMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProceduralMeshComponent* SelectionBoxMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProceduralMeshComponent* OutlineMesh;

	UPROPERTY(BlueprintReadOnly)
	UMaterialInstanceDynamic* LineMaterialInstance;

	UPROPERTY(BlueprintReadOnly)
	UMaterialInstanceDynamic* SelectionMaterialInstance;

	UPROPERTY(BlueprintReadOnly)
	UMaterialInstanceDynamic* OutlineMaterialInstance;
	
	UPROPERTY(EditAnywhere, Category = "Grid Properties")
	UMaterialInterface *ParentMaterial;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	int32 NumRows = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	int32 NumColumns = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	float TileSize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	float LineThickness = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	FLinearColor LineColor = FLinearColor(1, 0, 0, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	FLinearColor SelectionColor = FLinearColor(1, 1, 0, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	FLinearColor OutlineColor = FLinearColor(0, 1, 0, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	float LineOpacity = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	float SelectionOpacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Properties")
	float OutlineOpacity = 1.0f;

	UFUNCTION(BlueprintCallable)
	void DrawGrid();

	UFUNCTION()
	void DrawGridLine(int32 Index, FVector StartPoint, FVector EndPoint, float Thickness);

	UFUNCTION(BlueprintCallable)
	void DrawSelectionBox();

	UFUNCTION()
	void CreateSelectionBoxMesh(int32 Index, FVector StartPoint,FVector EndPoint, float Thickness);

	UFUNCTION()
	void CreateOutlineMesh(int32 BottomRow, int32 TopRow, int32 LeftColumn, int32 RightColumn);

private:

	UPROPERTY()
	TArray<int32> Triangles;

	int PlayerRange = 1;
	FVector* SelectionBoxPosition = new FVector(0, 0, 0);

	FVector* SelectionBoxCenter = new FVector(0, 0, 0);

	UFUNCTION()
	void DrawHorizontalLines();

	UFUNCTION()
	void DrawVerticalLines();

	UFUNCTION()
	float GetWidth() const;

	UFUNCTION()
	float GetHeight() const;

	UFUNCTION()
	TArray<FVector> GetVertices(const FVector &StartPoint, const FVector &EndPoint, float Thickness) const;

	
	void SetTriangles(FVector TopTriVerts, FVector BottomTriVerts, TArray<int32>& TriangleVerticeIndex) const;

	UFUNCTION()
	UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor MaterialColor, float MaterialOpacity);
	
};
