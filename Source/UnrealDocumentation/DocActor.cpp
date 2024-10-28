// Fill out your copyright notice in the Description page of Project Settings.


#include "DocActor.h"

// Sets default values
ADocActor::ADocActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADocActor::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	
}

// Called every frame
void ADocActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

