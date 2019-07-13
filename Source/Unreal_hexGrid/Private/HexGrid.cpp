// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGrid.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/Classes/Components/TextRenderComponent.h"

// Sets default values
AHexGrid::AHexGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	createGrid();
}

// Called when the game starts or when spawned
void AHexGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexGrid::createGrid()
{
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));



	UTextRenderComponent* Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	Text->SetupAttachment(RootComponent);
	Text->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	Text->SetRelativeLocation(FVector(0.0f, 0.0f, 6.0f));
	Text->SetHorizontalAlignment(EHTA_Center);
	Text->SetVerticalAlignment(EVRTA_TextCenter);
	Text->SetTextRenderColor(FColor(0, 0, 0, 1));
	Text->SetWorldSize(150.0f);

	//TODO Refactor, and loop, check catlike coding tutorial
}

void AHexGrid::createCell(int x, int y)
{
	// Create and position a mesh component so we can see where our sphere is
	UStaticMeshComponent* PlaneVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	PlaneVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
	if (SphereVisualAsset.Succeeded())
	{
		PlaneVisual->SetStaticMesh(SphereVisualAsset.Object);
		PlaneVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
		PlaneVisual->SetWorldScale3D(FVector(0.8f));
	}
}


