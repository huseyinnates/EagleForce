// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Camera/CameraComponent.h>
#include <Components/PostProcessComponent.h>
#include "UAVPawn.generated.h"


UCLASS()
class UNREALDOCUMENTATION_API AUAVPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUAVPawn();
	//create custom camera component
	UPROPERTY(VisibleAnywhere, Category = "Camera Component")
	UCameraComponent* UAVCamera;
	//Using mouse wheel zoom in and out
	void ZoomInOut(float WheelAxis); 
	//Zoom speed
	UPROPERTY(EditAnywhere, Category = "Camera Component")
	float ZoomSpeed = 5.0f;
	//Black and white material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
	UMaterialInterface* BlackAndWhiteMaterial;
	//Render black and white
	void RenderBlackAndWhite();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
