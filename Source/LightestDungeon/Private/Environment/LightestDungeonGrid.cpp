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

}

// Called when the game starts or when spawned
void ALightestDungeonGrid::BeginPlay()
{
	Super::BeginPlay();
	
}


