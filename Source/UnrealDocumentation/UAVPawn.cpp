// UAVPawn.cpp

#include "UAVPawn.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AUAVPawn::AUAVPawn()
{
    // Set this pawn to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create the camera component
    UAVCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("UAVCamera"));
    UAVCamera->SetupAttachment(RootComponent);
    UAVCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f)); // Position the camera
    UAVCamera->bUsePawnControlRotation = true; // Let the controller rotate the camera

    // Initialize TargetFOV with the default FOV
    TargetFOV = UAVCamera->FieldOfView;

    // Create the post-process component
    PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
    PostProcessComponent->SetupAttachment(UAVCamera);
    PostProcessComponent->bEnabled = false; // Initially disabled

    // Create the floating movement component
    FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
    FloatingMovement->UpdatedComponent = RootComponent;

    // Load default black and white material
    static ConstructorHelpers::FObjectFinder<UMaterial> BWMaterial(TEXT("/Game/Materials/CameraMaterials/M_BlackAndWhite"));
    if (BWMaterial.Succeeded())
    {
        BlackAndWhiteMaterial = BWMaterial.Object;
    }

    // Load default thermal material
    static ConstructorHelpers::FObjectFinder<UMaterial> ThermalMat(TEXT("/Game/Materials/CameraMaterials/M_Thermal"));
    if (ThermalMat.Succeeded())
    {
        ThermalMaterial = ThermalMat.Object;
    }
}

// Called when the game starts or when spawned
void AUAVPawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AUAVPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Smoothly interpolate the FOV towards the TargetFOV
    if (UAVCamera)
    {
        float CurrentFOV = UAVCamera->FieldOfView;
        float NewFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, ZoomInterpSpeed);
        UAVCamera->SetFieldOfView(NewFOV);
    }
}

// Called to bind functionality to input
void AUAVPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind movement axes
    PlayerInputComponent->BindAxis("MoveForward", this, &AUAVPawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AUAVPawn::MoveRight);
    PlayerInputComponent->BindAxis("MoveUp", this, &AUAVPawn::MoveUp);

    // Bind look axes
    PlayerInputComponent->BindAxis("Turn", this, &AUAVPawn::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AUAVPawn::LookUp);

    // Bind zoom
    PlayerInputComponent->BindAxis("Zoom", this, &AUAVPawn::ZoomInOut);

    // Bind post-process toggle
    PlayerInputComponent->BindAction("TogglePostProcess", IE_Pressed, this, &AUAVPawn::TogglePostProcess);
}

void AUAVPawn::MoveForward(float AxisValue)
{
    if (FloatingMovement && (Controller != nullptr) && (AxisValue != 0.0f))
    {
        // Determine which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        FloatingMovement->AddInputVector(Direction * AxisValue);
    }
}

void AUAVPawn::MoveRight(float AxisValue)
{
    if (FloatingMovement && (Controller != nullptr) && (AxisValue != 0.0f))
    {
        // Determine which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        FloatingMovement->AddInputVector(Direction * AxisValue);
    }
}

void AUAVPawn::MoveUp(float AxisValue)
{
    if (FloatingMovement && (AxisValue != 0.0f))
    {
        // Move up or down along the Z-axis
        const FVector Direction = FVector(0.0f, 0.0f, 1.0f);
        FloatingMovement->AddInputVector(Direction * AxisValue);
    }
}

void AUAVPawn::Turn(float AxisValue)
{
    AddControllerYawInput(AxisValue);
}

void AUAVPawn::LookUp(float AxisValue)
{
    AddControllerPitchInput(AxisValue);
}

void AUAVPawn::ZoomInOut(float WheelAxis)
{
    if (UAVCamera)
    {
        // Update TargetFOV based on wheel input
        TargetFOV -= (WheelAxis * ZoomSpeed); // "-" ile zoom in yaparken FOV'u küçültüyoruz
        TargetFOV = FMath::Clamp(TargetFOV, MinFOV, MaxFOV);
    }
}

void AUAVPawn::RenderBlackAndWhite()
{
    if (BlackAndWhiteMaterial && PostProcessComponent)
    {
        // Enable post-process and apply black and white material
        PostProcessComponent->AddOrUpdateBlendable(BlackAndWhiteMaterial);
        PostProcessComponent->bEnabled = true;
    }
}

void AUAVPawn::RenderThermal()
{
    if (ThermalMaterial && PostProcessComponent)
    {
        // Enable post-process and apply thermal material
        PostProcessComponent->AddOrUpdateBlendable(ThermalMaterial);
        PostProcessComponent->bEnabled = true;
    }
}

void AUAVPawn::TogglePostProcess()
{
    if (PostProcessComponent)
    {
        if (PostProcessComponent->bEnabled)
        {
            // Disable post-process
            PostProcessComponent->bEnabled = false;
        }
        else
        {
            // Toggle between black and white and thermal for demonstration
            // You can implement a more sophisticated toggle mechanism as needed
			UE_LOG(LogTemp, Warning, TEXT("Toggling post-process effect"));
            if (BlackAndWhiteMaterial)
            {
                RenderBlackAndWhite();
                UE_LOG(LogTemp, Warning, TEXT("BLACK AND WHITE"));
            }
            else if (ThermalMaterial)
            {
                RenderThermal();
                UE_LOG(LogTemp, Warning, TEXT("THERMAL CAMERA"));
            }
        }
    }
}
