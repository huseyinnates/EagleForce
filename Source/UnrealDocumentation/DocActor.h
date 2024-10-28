// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DocActor.generated.h"

UCLASS()
class UNREALDOCUMENTATION_API ADocActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADocActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;


};
