// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "CoreExploration.generated.h"

UCLASS()
class UNREALDOCUMENTATION_API ACoreExploration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoreExploration();
	//Add a UStaticMeshComponent to the actor
	UPROPERTY(EditAnywhere,Category="Mesh Component Documentation")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere,Category="Mesh Component Documentation")
	UStaticMesh* MeshAsset;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Helper function for the CoreExploration class
	UFUNCTION(BlueprintCallable) 
	FString PrintResult();

};
