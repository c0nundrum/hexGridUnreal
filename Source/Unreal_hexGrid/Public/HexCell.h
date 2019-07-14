// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "HexCell.generated.h"
UCLASS()
class UNREAL_HEXGRID_API AHexCell : public AActor
{
	GENERATED_BODY()

	struct Triangle {
		FVector v1;
		FVector v2;
		FVector v3;
	};
	
public:	
	// Sets default values for this actor's properties
	AHexCell();
	void CreateTriangle(TArray<Triangle> triangles);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FVector center;
	void prepareScene();
	UProceduralMeshComponent * mesh;

};
