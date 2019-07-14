// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexMetrics.h"
#include "ProceduralMeshComponent.h"
#include "Grid.generated.h"

UCLASS()
class UNREAL_HEXGRID_API AGrid : public AActor
{
	GENERATED_BODY()

struct Triangle {
	FVector v1;
	FVector v2;
	FVector v3;
	};
	
public:

	// Sets default values for this actor's properties
	AGrid();
	void CreateTriangle(FVector, FVector, FVector);
	void CreateTriangle(TArray<Triangle> triangles);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostLoad() override;
	virtual void PostActorCreated() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent * mesh;

	////DEBUG vectors
	//FVector v1 = FVector(0, 0, 0);
	//FVector v2 = FVector(0, 100, 0);
	//FVector v3 = FVector(0, 0, 100);

	//static float outerRadius;
	//static float innerRadius;

	/*TArray<FVector> VectorArray;*/

	FVector center;

	void prepareScene();

};