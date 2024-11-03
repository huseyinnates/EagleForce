// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <JSBSimMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "EagleAircraft.generated.h"


UCLASS()
class UNREALDOCUMENTATION_API AEagleAircraft : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEagleAircraft();

	//Add SkeletalMeshComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Eagle|Aircraft")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	//Add spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Eagle|Aircraft")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	//Add camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Eagle|Aircraft")
	TObjectPtr<UCameraComponent> CameraComponent;

	//Add JSBSimMovementComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Eagle|Aircraft")
	TObjectPtr<UJSBSimMovementComponent> JSBSimMovementComponent;

	void RotateCamera(float AxisValue);
	void ThrottleUp();
	void ThrottleDown();
	void Elevator(float AxisValue);
	void Aileron(float AxisValue);
	void Rudder(float AxisValue);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
