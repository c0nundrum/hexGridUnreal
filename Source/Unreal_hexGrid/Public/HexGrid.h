// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGrid.generated.h"


UCLASS()
class UNREAL_HEXGRID_API AHexGrid : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AHexGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostActorCreated() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

public:	
	UPROPERTY(EditAnywhere)
	int32 height = 10;

	UPROPERTY(EditAnywhere)
	int32 width = 10;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void createGrid();
	void createCell(int, int, int);

	void createHexCell(int, int, int);
	
	TArray<UStaticMeshComponent*> cells;
	TArray<AActor*> cellsA;
	TArray<UPrimitiveComponent*> cellNumbers;

};
