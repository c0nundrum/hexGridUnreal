// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Engine/Classes/Components/TextRenderComponent.h"
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
	
private:
	void CreateTriangle(TArray<Triangle> triangles);
	UMaterialInstanceDynamic* DynMMaterial;
	FVector center;
	void prepareScene();
	UProceduralMeshComponent * mesh;



public:	
	// Sets default values for this actor's properties
	AHexCell();
	void SetCoordinate(int x, int y);

	UPROPERTY(VisibleAnywhere)
		int32 iXCoordinate;

	UPROPERTY(VisibleAnywhere)
		int32 iYCoordinate;

	UPROPERTY(VisibleAnywhere)
		UTextRenderComponent* cellLocation;

	UPROPERTY(VisibleAnywhere)
		UMaterial* MMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostActorCreated() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	

};
