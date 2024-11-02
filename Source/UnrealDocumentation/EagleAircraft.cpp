// Fill out your copyright notice in the Description page of Project Settings.


#include "EagleAircraft.h"

// Sets default values
AEagleAircraft::AEagleAircraft()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create SkeletalMeshComponent
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AircraftSkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());

	//Create SpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(SkeletalMeshComponent);

	//Create CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	//Create JSBSimMovementComponent
	JSBSimMovementComponent = CreateDefaultSubobject<UJSBSimMovementComponent>(TEXT("JSBSimMovementComponent"));
}

void AEagleAircraft::RotateCamera(float AxisValue)
{
	FRotator NewRotation = SpringArmComponent->GetComponentRotation();
	NewRotation.Yaw += AxisValue;
	SpringArmComponent->SetWorldRotation(NewRotation);
}
// Called when the game starts or when spawned
void AEagleAircraft::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEagleAircraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEagleAircraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//bind axis input for camera rotation
	PlayerInputComponent->BindAxis("RotateCamera", this, &AEagleAircraft::RotateCamera);
}

