// Fill out your copyright notice in the Description page of Project Settings.


#include "UAVPawn.h"


// Sets default values
AUAVPawn::AUAVPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UAVCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("UAVCamera"));
	UPostProcessComponent* PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
	PostProcessComponent->SetupAttachment(RootComponent);

	// Varsayılan siyah beyaz materyalini yükle
	//static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/Materials/CameraMaterials/BlackAndWhiteRenderMaterial"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/Materials/CameraMaterials/Material"));

	if (Material.Succeeded())
	{
		ThermalMaterial = Material.Object;
		PostProcessComponent->AddOrUpdateBlendable(ThermalMaterial);
	}
}

// Called when the game starts or when spawned
void AUAVPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUAVPawn::ZoomInOut(float WheelAxis)
{
	//Clamp the field of view to a minimum of 30 and a maximum of 90
	float FieldOfView = UAVCamera->FieldOfView;
	FieldOfView = FMath::Clamp(FieldOfView+(WheelAxis*ZoomSpeed), 20.0f, 120.0f);
	UAVCamera->SetFieldOfView(FieldOfView); 
}

void AUAVPawn::RenderBlackAndWhite()
{
	 
}
// Called every frame
void AUAVPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUAVPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Bind the mouse wheel to the ZoomInOut function
	PlayerInputComponent->BindAxis("ZoomInOut", this, &AUAVPawn::ZoomInOut);

}

