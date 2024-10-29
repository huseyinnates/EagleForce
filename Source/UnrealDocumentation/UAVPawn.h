// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Camera/CameraComponent.h>
#include <Components/PostProcessComponent.h>
#include "GameFramework/FloatingPawnMovement.h"
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

	// Floating Pawn Movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* FloatingMovement;
	 
	// Using mouse wheel zoom in and out
	void ZoomInOut(float WheelAxis);

	// Zoom speed
	UPROPERTY(EditAnywhere, Category = "Camera Component")
	float ZoomSpeed = 5.0f;

	// Zoom interpolation speed
	UPROPERTY(EditAnywhere, Category = "Camera Component")
	float ZoomInterpSpeed = 10.0f;

	// Minimum and Maximum FOV values
	UPROPERTY(EditAnywhere, Category = "Camera Component")
	float MinFOV = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Camera Component")
	float MaxFOV = 120.0f; 
	//Black and white material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
	UMaterialInterface* BlackAndWhiteMaterial;
	UMaterialInterface* ThermalMaterial;
	
	// Render black and white
	void RenderBlackAndWhite();

	// Render thermal
	void RenderThermal();

	// Toggle post-process effect
	void TogglePostProcess();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Look up/down
	void LookUp(float AxisValue);

	// Turn left/right
	void Turn(float AxisValue);

	// Move forward/backward
	void MoveForward(float AxisValue);

	// Move right/left
	void MoveRight(float AxisValue);

	// Move up/down
	void MoveUp(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	// Post-process component
	UPROPERTY(VisibleAnywhere, Category = "PostProcess")
	UPostProcessComponent* PostProcessComponent;
	
	// Target Field of View for smooth zooming
	float TargetFOV;
};
