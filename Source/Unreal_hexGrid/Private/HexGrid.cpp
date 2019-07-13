// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGrid.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/Classes/Components/TextRenderComponent.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"


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

	const int32 height = 10;
	const int32 width = 10;

	//We got an array of cells that should be equal to height * width

	for (int z = 0, i = 0; z < height; z++) {
		for (int x = 0; x < width; x++) {
			createCell(x, z, i++);
		}
	}
	
}

void AHexGrid::createCell(int x, int y, int i)
{
	//Build location
	FVector Location = FVector(x * 10.f, y * 10.f, 0.f);

	//i is not in use yet
	//Should be equal to index on the given cell array

	FString IntAsString = "cell " + FString::FromInt(i);
	FName ConvertedFString = FName(*IntAsString);

	// Create and position plane on x y
	//UStaticMeshComponent* PlaneVisual = CreateDefaultSubobject<UStaticMeshComponent>(ConvertedFString);
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

	//Cast not working, cant array utextrendercomponent
	cellNumbers.Add(CreateDefaultSubobject<UTextRenderComponent>(ConvertedFString));
	UTextRenderComponent * myActor = Cast<UTextRenderComponent>(cellNumbers[i]);
	if (myActor) {
		myActor->SetupAttachment(RootComponent);
		myActor->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
		myActor->SetRelativeLocation(Location);
		myActor->SetHorizontalAlignment(EHTA_Center);
		myActor->SetVerticalAlignment(EVRTA_TextCenter);
		myActor->SetTextRenderColor(FColor(0, 0, 0, 1));
		myActor->SetWorldSize(15.0f);
		myActor->SetText(IntAsString);
	}

	//TODO - TIME TO REFACTOR HEXMETRICS!
}


