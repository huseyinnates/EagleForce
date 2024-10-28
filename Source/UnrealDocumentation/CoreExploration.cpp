// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreExploration.h"

// Sets default values
ACoreExploration::ACoreExploration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoreExploration::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoreExploration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
 
FString ACoreExploration::PrintResult()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(MeshAsset);
	Mesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	return FString::Printf(TEXT("Mesh added to the scene"));
}

