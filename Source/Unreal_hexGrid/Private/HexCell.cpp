// Fill out your copyright notice in the Description page of Project Settings.


#include "HexCell.h"
#include "HexMetrics.h"
#include "ProceduralMeshComponent.h"
#include "Engine/Classes/Materials/Material.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/Classes/Materials/MaterialInstanceDynamic.h"

#define LOCTEXT_NAMESPACE "Coordinates"

// Sets default values
AHexCell::AHexCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	// New in UE 4.17, multi-threaded PhysX cooking.
	mesh->bUseAsyncCooking = true;

	prepareScene();

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/materials/vtxColor.vtxColor'"));

	if (Material.Object != NULL)
	{
		MMaterial = (UMaterial*)Material.Object;
	}


	cellLocation = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
	cellLocation->SetTextRenderColor(FColor::Green);
	cellLocation->SetRelativeRotation(FRotator(90.0f, 0.0f, 180.0f));
	cellLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 1.0f));
	cellLocation->SetHorizontalAlignment(EHTA_Center);
	cellLocation->SetVerticalAlignment(EVRTA_TextCenter);
	cellLocation->AttachTo(RootComponent);
	//cellLocation->RegisterComponent();

}

void AHexCell::SetCoordinate(int x, int y)
{
	iXCoordinate = x;

	iYCoordinate = y;

	UE_LOG(LogTemp, Warning, TEXT("Setting coordinates %d %d"), iXCoordinate, iYCoordinate);

	FText coordinatesT = FText::Format(LOCTEXT("Coordinates", "{0}\n{1}"), iXCoordinate, iYCoordinate);
	FVector Location = GetActorLocation();
	
	cellLocation->SetText(coordinatesT);

}

// Called when the game starts or when spawned
void AHexCell::BeginPlay()
{
	Super::BeginPlay();
}

void AHexCell::PostActorCreated()
{
	Super::PostActorCreated();

	DynMMaterial = UMaterialInstanceDynamic::Create(MMaterial, this);

	mesh->SetMaterial(0, DynMMaterial);

}

void AHexCell::prepareScene()
{
	center = FVector(0, 0, 0);
	TArray<Triangle> triangles;
	for (int32 i = 0; i < 6; ++i)
	{
		Triangle t;
		t.v1 = center;
		t.v2 = center + HexMetrics::corners[i];
		t.v3 = center + HexMetrics::corners[i + 1];

		triangles.Emplace(t);
	}

	CreateTriangle(triangles);
}


// Called every frame
void AHexCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexCell::CreateTriangle(TArray<Triangle> triangles)
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

	mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, false);

	// Enable collision data
	//mesh->ContainsPhysicsTriMeshData(true);

	//Empty Arrays for safety
	vertices.Empty();
	Triangles.Empty();
	normals.Empty();
	tangents.Empty();
	vertexColors.Empty();
	UV0.Empty();
}

#undef LOCTEXT_NAMESPACE
