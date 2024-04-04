// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/LightestDungeonGrid.h"

#include "Kismet/KismetMaterialLibrary.h"


// Sets default values
ALightestDungeonGrid::ALightestDungeonGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	GridMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GridMesh"));
	GridMesh->SetupAttachment(Root);

	SelectionBoxMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("SelectionBoxMesh"));
	SelectionBoxMesh->SetupAttachment(Root);

	OutlineMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("OutlineMesh"));
	OutlineMesh->SetupAttachment(Root);

	const FVector& TopTriVerts = FVector(2, 1,  0);
	const FVector& BottomTriVerts = FVector(2, 3, 1);
	SetTriangles(TopTriVerts, BottomTriVerts, Triangles);
}

void ALightestDungeonGrid::DrawGrid()
{
	if(GridMesh)
	{
		GridMesh->ClearAllMeshSections();
		
	}
	
	LineMaterialInstance = CreateMaterialInstance(LineColor, LineOpacity);
	DrawHorizontalLines();
	DrawVerticalLines();
}

// Called when the game starts or when spawned
void ALightestDungeonGrid::BeginPlay()
{
	Super::BeginPlay();
}

void ALightestDungeonGrid::DrawHorizontalLines()
{
	//for loop to draw horizontal lines based number of rows
	for(int i = 0; i < NumRows + 1; i++)
	{
		const float LineStart = i * TileSize;
		const float LineEnd = GetWidth();
		const FVector &StartPoint = FVector(LineStart, 0, 0);
		const FVector &EndPoint = FVector(LineStart, LineEnd, 0);
		DrawGridLine(i, StartPoint, EndPoint, LineThickness);
	}
}

void ALightestDungeonGrid::DrawVerticalLines()
{
	for(int i = 0; i < NumColumns +1; i++)
	{
		const float &LineStart = i * TileSize;
		const float &LineEnd = GetHeight();
		const FVector &StartPoint = FVector(0, LineStart, 0);
		const FVector &EndPoint = FVector(LineEnd, LineStart, 0);

		DrawGridLine(i + NumRows + 1, StartPoint, EndPoint, LineThickness);
	}
}

void ALightestDungeonGrid::DrawGridLine(int32 Index, FVector StartPoint,FVector EndPoint, float Thickness)
{
	const TArray<FVector> Vertices = GetVertices(StartPoint, EndPoint, Thickness);

	//empty arrays needed to create mesh section
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;
	
	GridMesh->CreateMeshSection_LinearColor(Index, Vertices, Triangles, Normals, UV0, VertexColors, Tangents ,true);
	GridMesh->SetMaterial(Index, LineMaterialInstance);
	
	
}

//Called in blueprint
void ALightestDungeonGrid::DrawSelectionBox()
{
	if(SelectionBoxMesh)
	{
		SelectionBoxMesh->ClearAllMeshSections();
	}
	SelectionMaterialInstance = CreateMaterialInstance(SelectionColor, SelectionOpacity);

	FVector* StartPoint = new FVector(0, TileSize/2, 0);
	FVector* EndPoint = new FVector(TileSize, TileSize/2, 0);
	CreateSelectionBoxMesh(0, *StartPoint, *EndPoint, TileSize);
}


void ALightestDungeonGrid::CreateSelectionBoxMesh(int32 Index, FVector StartPoint, FVector EndPoint, float Thickness)
{
	const TArray<FVector> Vertices = GetVertices(StartPoint, EndPoint, Thickness);

	//empty arrays needed to create mesh section
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;
	
	SelectionBoxMesh->CreateMeshSection_LinearColor(Index, Vertices, Triangles, Normals, UV0, VertexColors, Tangents ,true);
	SelectionBoxMesh->SetMaterial(Index, SelectionMaterialInstance);
	SelectionBoxMesh->SetVisibility(false);
}



float ALightestDungeonGrid::GetWidth() const
{
	return NumColumns * TileSize;
}

float ALightestDungeonGrid::GetHeight() const
{
	return NumRows * TileSize;
}

TArray<FVector> ALightestDungeonGrid::GetVertices(const FVector &StartPoint, const FVector &EndPoint, float Thickness) const
{
	const FVector DirectionNormalized = (EndPoint - StartPoint).GetSafeNormal();
	const FVector UpVector = FVector(0, 0, 1);
	const FVector Cross = FVector::CrossProduct(DirectionNormalized, UpVector);
	const FVector LineThicknessDirection = Cross.GetSafeNormal();
	const float HalfLineThickness = Thickness / 2;
	
	const FVector Vertex0 = StartPoint + LineThicknessDirection * HalfLineThickness;
	const FVector Vertex1 = EndPoint + LineThicknessDirection * HalfLineThickness;
	const FVector Vertex2 = StartPoint - LineThicknessDirection * HalfLineThickness;
	const FVector Vertex3 = EndPoint - LineThicknessDirection * HalfLineThickness;

	TArray<FVector> Vertices;
	Vertices.Add(Vertex0);
	Vertices.Add(Vertex1);
	Vertices.Add(Vertex2);
	Vertices.Add(Vertex3);
	return Vertices;
}

void ALightestDungeonGrid::SetTriangles(FVector TopTriVerts, FVector BottomTriVerts, TArray<int32>& TriangleVerticeIndex) const
{
	TriangleVerticeIndex.Add(TopTriVerts.X);
	TriangleVerticeIndex.Add(TopTriVerts.Y);
	TriangleVerticeIndex.Add(TopTriVerts.Z);
	TriangleVerticeIndex.Add(BottomTriVerts.X);
	TriangleVerticeIndex.Add(BottomTriVerts.Y);
	TriangleVerticeIndex.Add(BottomTriVerts.Z);
}

UMaterialInstanceDynamic* ALightestDungeonGrid::CreateMaterialInstance(FLinearColor MaterialColor, float MaterialOpacity)
{
	UMaterialInstanceDynamic *MaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(
		this,
		ParentMaterial,
		"ParentMaterial"
	);

	MaterialInstance->SetVectorParameterValue("Color", MaterialColor);
	MaterialInstance->SetScalarParameterValue("Opacity", MaterialOpacity);
	return MaterialInstance;
}

void ALightestDungeonGrid::UpdateSelectionBoxPosition(FVector CursorPosition, bool& CursorOverGrid)
{
	
	int32 CursorRow, CursorColumn;
	LocationToTile(CursorPosition, CursorOverGrid, CursorRow, CursorColumn);

	if(CursorOverGrid)
	{
		//selection box should be visible...
		CurrentTile.Row = CursorRow;
		CurrentTile.Column = CursorColumn;
		TileToLocation(CursorRow, CursorColumn, *SelectionBoxPosition, *SelectionBoxCenter);

		SelectionBoxMesh->SetVisibility(true);
		SelectionBoxMesh->SetWorldLocation(*SelectionBoxPosition);
	}
	else
	{
		//selection box should be invisible...
		SelectionBoxMesh->SetVisibility(false);
	}
}

FVector ALightestDungeonGrid::GetSelectionBoxCenter() const
{
	return *SelectionBoxCenter;
}

TArray<FTileCoords> ALightestDungeonGrid::GetTilesInPlayerRange(int PlayerRange) const
{
	TArray<FTileCoords> TilesInPlayerRange;

	for(int i = 0; i <= NumRows; i++)
	{
		for(int k = 0; k <= NumColumns; k++)
		{
			if(CurrentTile.Row -1 < 0)
				continue;

			if(i >= CurrentTile.Row - PlayerRange && i <= CurrentTile.Row + PlayerRange)
			{
				if(k >= CurrentTile.Column - PlayerRange && k <= CurrentTile.Column + PlayerRange)
				{
					FTileCoords Tile = FTileCoords(i, k);
					TilesInPlayerRange.Add(Tile);
				}
			}
		}
	}
	return TilesInPlayerRange;
}

void ALightestDungeonGrid::OutlineReachableTiles()
{
	TArray<FTileCoords> TilesInPlayerRange = GetTilesInPlayerRange(1);
	int BottomRow = 0;
	int TopRow = 0;
	int LeftColumn = 0;
	int RightColumn= 0;
	for(int i = 0; i < TilesInPlayerRange.Num(); i++)
	{
		FTileCoords Tile = TilesInPlayerRange[i];
		if(i == 0)
		{
			BottomRow = Tile.Row;
			TopRow = Tile.Row;
			LeftColumn = Tile.Column;
			RightColumn = Tile.Column;
		}

		if(Tile.Row < BottomRow)
		{
			BottomRow = Tile.Row;
		}

		if(Tile.Row > TopRow)
		{
			TopRow = Tile.Row;
		}

		if(Tile.Column < LeftColumn)
		{
			LeftColumn = Tile.Column;
		}

		if(Tile.Column > RightColumn)
		{
			RightColumn = Tile.Column;
		}
	}

	FVector StartPoint;
	FVector Center;
	TileToLocation(BottomRow, LeftColumn, StartPoint, Center);
	

	
}

void ALightestDungeonGrid::SetPlayerRange(int Range)
{
	PlayerRange = Range;
	//Make outline mesh and set visibility to false
}

void ALightestDungeonGrid::LocationToTile(FVector Location, bool& IsValid, int32& Row, int32& Column) const
{
	const float GridXPosition = GetActorLocation().X;
	const float MouseXPosition = Location.X;
	Row = FMath::FloorToInt((MouseXPosition - GridXPosition) / GetWidth() * NumRows);
	
	const float GridYPosition = GetActorLocation().Y;
	const float MouseYPosition = Location.Y;
	const float CurrentColumn = FMath::FloorToInt((MouseYPosition - GridYPosition) / GetHeight() * NumColumns);
	Column = FMath::FloorToInt((MouseYPosition - GridYPosition) / GetHeight() * NumColumns);
	
	IsValid = IsTileValid(Row, Column);
}

void ALightestDungeonGrid::TileToLocation(int32 Row, int32 Column, FVector& Location, FVector& Center) const
{
	float GridXPosition = GetActorLocation().X;
	float GridYPosition = GetActorLocation().Y;

	float TileLocalXPosition = Row * TileSize;
	float TileLocalYPosition = Column * TileSize;

	float TileWorldXPosition = GridXPosition + TileLocalXPosition;
	float TileWorldYPosition = GridYPosition + TileLocalYPosition;
	Location = FVector(TileWorldXPosition, TileWorldYPosition, GetActorLocation().Z);

	Center = FVector(Location.X + TileSize / 2, Location.Y + TileSize / 2, Location.Z);
}

void ALightestDungeonGrid::SetSelectedTile(int32 Row, int32 Column)
{
	
}

bool ALightestDungeonGrid::IsTileValid(int32 Row, int32 Column) const
{

	if (Row >= 0 && Row < NumRows && Column >= 0 && Column < NumColumns)
	{
		return true;
	}
	return false;
}



