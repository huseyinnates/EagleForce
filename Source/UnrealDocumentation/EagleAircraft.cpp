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

void AEagleAircraft::ThrottleUp()
{
	for (int i = 0; i < JSBSimMovementComponent->EngineCommands.Num(); i++)
	{
		JSBSimMovementComponent->EngineCommands[i].Throttle += .1f; 
	}
}
 
void AEagleAircraft::ThrottleDown()
{
	for (int i = 0; i < JSBSimMovementComponent->EngineCommands.Num(); i++)
	{
		JSBSimMovementComponent->EngineCommands[i].Throttle -= 100.0f; 
	}
}

void AEagleAircraft::Elevator(float AxisValue)
{
	JSBSimMovementComponent->Commands.Elevator = AxisValue;
}

void AEagleAircraft::Aileron(float AxisValue)
{
	JSBSimMovementComponent->Commands.Aileron = AxisValue;
}

void AEagleAircraft::Rudder(float AxisValue)
{
	JSBSimMovementComponent->Commands.Rudder = AxisValue;
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
	//bind input for throttle up
	PlayerInputComponent->BindAction("ThrottleUp", IE_Repeat, this, &AEagleAircraft::ThrottleUp);
	//bind input for throttle down
	PlayerInputComponent->BindAction("ThrottleDown", IE_Repeat, this, &AEagleAircraft::ThrottleDown);
	//bind axis input for elevator
	PlayerInputComponent->BindAxis("Elevator", this, &AEagleAircraft::Elevator);
	//bind axis input for aileron
	PlayerInputComponent->BindAxis("Aileron", this, &AEagleAircraft::Aileron);
	//bind axis input for rudder
	PlayerInputComponent->BindAxis("Rudder", this, &AEagleAircraft::Rudder);
}

