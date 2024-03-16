// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/LightestDungeonGrid.h"

// Sets default values
ALightestDungeonGrid::ALightestDungeonGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	GridMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GridMesh"));
	GridMesh->SetupAttachment(Root);

	const FVector& TopTriVerts = FVector(2, 1,  0);
	const FVector& BottomTriVerts = FVector(2, 3, 1);
	SetTriangles(TopTriVerts, BottomTriVerts, Triangles);

	DrawGrid();
}

void ALightestDungeonGrid::DrawGrid()
{
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
		DrawLine(i, StartPoint, EndPoint);
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

		DrawLine(i + NumRows + 1, StartPoint, EndPoint);
	}
}

void ALightestDungeonGrid::DrawLine(int32 Index, FVector StartPoint,FVector EndPoint)
{
	const TArray<FVector> Vertices = GetVertices(StartPoint, EndPoint);

	//empty arrays needed to create mesh section
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;
	GridMesh->CreateMeshSection_LinearColor(Index, Vertices, Triangles, Normals, UV0, VertexColors, Tangents ,true);
}



float ALightestDungeonGrid::GetWidth() const
{
	return NumColumns * TileSize;
}

float ALightestDungeonGrid::GetHeight() const
{
	return NumRows * TileSize;
}

TArray<FVector> ALightestDungeonGrid::GetVertices(const FVector &StartPoint, const FVector &EndPoint) const
{
	const FVector DirectionNormalized = (EndPoint - StartPoint).GetSafeNormal();
	const FVector UpVector = FVector(0, 0, 1);
	const FVector Cross = FVector::CrossProduct(DirectionNormalized, UpVector);
	const FVector LineThicknessDirection = Cross.GetSafeNormal();
	const float HalfLineThickness = LineThickness / 2;
	
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

UMaterialInstanceDynamic* ALightestDungeonGrid::CreateMaterialInstance(FLinearColor Color, float Opacity)
{
	UMaterialInstanceDynamic *MaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(
		this,
		ParentMaterial,
		"ParentMaterial"
	);

	MaterialInstance->SetVectorParameterValue("Color", Color);
	MaterialInstance->SetScalarParameterValue("Opacity", Opacity);


	return MaterialInstance;
}

void ALightestDungeonGrid::LocationToTile(FVector Location, bool IsValid, int32& Row, int32& Column)
{
}

void ALightestDungeonGrid::TileToLocation(int32 Row, int32 Column, bool IsCenter, bool& IsValid, FVector2D& Location)
{
}

void ALightestDungeonGrid::SetSelectedTile(int32 Row, int32 Column)
{
}

bool ALightestDungeonGrid::IsTileValid(int32 Row, int32 Column) const
{
	return false;
}


