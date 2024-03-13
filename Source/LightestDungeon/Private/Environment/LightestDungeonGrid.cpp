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

	LineMaterialInstance = CreateMaterialInstance(LineColor, LineOpacity);
	SelectionMaterialInstance = CreateMaterialInstance(SelectionColor, SelectionOpacity);
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

// Called when the game starts or when spawned
void ALightestDungeonGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALightestDungeonGrid::DrawHorizontalLines()
{
	//for loop to draw horizontal lines based number of rows
	for(int i = 0; i < NumRows; i++)
	{
		float LineStart = i * TileSize;
		float LineEnd = GetWidth();
		FVector StartPoint = FVector(LineStart, 0, 0);
		FVector EndPoint = FVector(LineStart, LineEnd, 0);
		TArray<FVector> Vertices;
		TArray<int32> Triangles;
		DrawLine(StartPoint, EndPoint, LineThickness, Vertices, Triangles);
	}
}

void ALightestDungeonGrid::DrawVerticalLines()
{
	
}


void ALightestDungeonGrid::DrawLine(
	FVector Start,
	FVector End,
	float Thickness,
	TArray<FVector>& Vertices,
	TArray<int32>& Triangles)
{
	
}



float ALightestDungeonGrid::GetWidth() const
{
	return NumColumns * TileSize;
}

float ALightestDungeonGrid::GetHeight() const
{
	return NumRows * TileSize;
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


