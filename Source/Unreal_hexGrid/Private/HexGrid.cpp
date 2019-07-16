// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGrid.h"
#include "HexMetrics.h"
#include "HexCell.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/Classes/Components/TextRenderComponent.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"
#include "Core/Public/Internationalization/Text.h"
#include "Engine/Classes/Components/ChildActorComponent.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"


#define LOCTEXT_NAMESPACE "Coordinates"


// Sets default values
AHexGrid::AHexGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	
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

void AHexGrid::PostActorCreated()
{
	Super::PostActorCreated();
	createGrid();
	
}

void AHexGrid::createGrid()
{
	//We got an array of cells that should be equal to height * width

	for (int z = 0, i = 0; z < height; z++) {
		for (int x = 0; x < width; x++) {
			//createCell(x, z, i++);
			createHexCell(x, z, i++);
		}
	}
	
}

void AHexGrid::createCell(int x, int y, int i)
{

	//Build location
	FVector Location = FVector(
		(x + y * 0.5f - y / 2) * (HexMetrics::innerRadius * 2.0f), 
		y * (HexMetrics::outerRadius * 1.5f),
		0.f);

	FString IntAsString = "cell " + FString::FromInt(i);
	FName ConvertedFString = FName(*IntAsString);

	// Create and position plane on x y
	cells.Add(CreateDefaultSubobject<UStaticMeshComponent>(ConvertedFString));
	cells[i]->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
	if (SphereVisualAsset.Succeeded())
	{

		cells[i]->SetStaticMesh(SphereVisualAsset.Object);
		cells[i]->SetRelativeLocation(Location);
		cells[i]->SetWorldScale3D(FVector(1.0f));
	}

	IntAsString = "CountdownNumber " + FString::FromInt(i);
	ConvertedFString = FName(*IntAsString);

	FText coordinatesT = FText::Format(LOCTEXT("Coordinates", "{0}\n{1}"), x, y);


	cellNumbers.Add(CreateDefaultSubobject<UTextRenderComponent>(ConvertedFString));
	UTextRenderComponent * coordinatesRenderComp = Cast<UTextRenderComponent>(cellNumbers[i]);
	if (coordinatesRenderComp) {
		coordinatesRenderComp->SetupAttachment(RootComponent);
		coordinatesRenderComp->SetRelativeRotation(FRotator(90.0f, 0.0f, 180.0f));
		coordinatesRenderComp->SetRelativeLocation(FVector(Location.X, Location.Y, Location.Z + 1.0f));
		coordinatesRenderComp->SetHorizontalAlignment(EHTA_Center);
		coordinatesRenderComp->SetVerticalAlignment(EVRTA_TextCenter);
		coordinatesRenderComp->SetTextRenderColor(FColor(0, 0, 0, 1));
		coordinatesRenderComp->SetWorldSize(30.0f);
		coordinatesRenderComp->SetText(coordinatesT);
	}
}

void AHexGrid::createHexCell(int x, int y, int i)
{
	//Build location
	FVector Location = FVector(
		(x + y * 0.5f - y / 2) * (HexMetrics::innerRadius * 2.0f),
		y * (HexMetrics::outerRadius * 1.5f),
		0.f);

	FString IntAsString = "cell " + FString::FromInt(i);
	FName ConvertedFString = FName(*IntAsString);

	//Messes up if called from constructor
	//UChildActorComponent* cell = CreateDefaultSubobject<UChildActorComponent>(ConvertedFString);
	//cell->bEditableWhenInherited = true;
	//cell->SetupAttachment(RootComponent);
	//cell->RegisterComponent();
	//cell->SetRelativeLocation(Location);
	//cell->SetChildActorClass(AHexCell::StaticClass());
	//cell->CreateChildActor();

	//Cant be called from constructor
	UChildActorComponent* cell = NewObject<UChildActorComponent>(this);
	cell->bEditableWhenInherited = true;
	cell->SetupAttachment(RootComponent);
	cell->SetRelativeLocation(Location);
	cell->RegisterComponent();
	cell->SetChildActorClass(AHexCell::StaticClass());
	cell->CreateChildActor();

	//AHexCell* aCell = Cast<AHexCell>(cell);
}


