// Fill out your copyright notice in the Description page of Project Settings.
#include "Grid.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	// New in UE 4.17, multi-threaded PhysX cooking.
	mesh->bUseAsyncCooking = true;

}

// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void AGrid::PostActorCreated()
{
	Super::PostActorCreated();
	prepareScene();
	
}

// This is called when actor is already in level and map is opened
void AGrid::PostLoad()
{
	Super::PostLoad();
	prepareScene();

}


// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	prepareScene();
	
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrid::prepareScene()
{
	center = FVector(0, 0, 0);
	TArray<Triangle> triangles;
	for (int32 i = 0; i < 6 ; ++i)
	{
		Triangle t;
		t.v1 = center;
		t.v2 = center + HexMetrics::corners[i];
		t.v3 = center + HexMetrics::corners[i + 1];
		
		triangles.Emplace(t);
	}

	CreateTriangle(triangles);
}

void AGrid::CreateTriangle(FVector v1, FVector v2, FVector v3)
{
	TArray<FVector> vertices;
	vertices.Add(v1);
	vertices.Add(v2);
	vertices.Add(v3);

	TArray<int32> Triangles;
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	TArray<FVector> normals;
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));


	TArray<FProcMeshTangent> tangents;
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));

	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

	mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);

	// Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);
}

void AGrid::CreateTriangle(TArray<Triangle> triangles)
{
	TArray<FVector> vertices;
	for (auto& t : triangles)
	{
		vertices.Add(t.v1);
		vertices.Add(t.v2);
		vertices.Add(t.v3);
		
	}
	
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;
	TArray<FVector2D> UV0;

	for (int32 Index = 0; Index != vertices.Num(); ++Index)
	{
		Triangles.Add(Index);
		normals.Add(FVector(1, 0, 0));
		tangents.Add(FProcMeshTangent(0, 1, 0));
		vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

		//Bad UV translation
		UV0.Add(FVector2D(vertices[Index].X, vertices[Index].Y));

	}

	mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);

	// Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);
}