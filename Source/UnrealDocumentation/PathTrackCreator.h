// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SplineComponent.h>
#include "CesiumGeoreference.h"
#include "CesiumGlobeAnchorComponent.h"
#include "CesiumGlobeAnchoredActorComponent.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/DataTable.h"
#include "HAL/PlatformFilemanager.h"
#include "UObject/TextProperty.h"
#include "PathTrackCreator.generated.h"

UCLASS()
class UNREALDOCUMENTATION_API APathTrackCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathTrackCreator();
	~APathTrackCreator();
	// An Unreal Engine data table to store the raw flight data
	UPROPERTY(EditAnywhere, Category = "Tracker Data Table")
	UDataTable* RecorderDataTable;
	//Add data table for the UAVRawDataTable
	UFUNCTION(BlueprintCallable, Category = "Tracker Data Table")
	void AddRowToTable(double Longitude, double Latitude, double Height);
	void SaveDataTableToCSV(UDataTable* DataTable);
	UPROPERTY(EditAnywhere, Category = "Tracker Data Table")
	FString FileName = "FlightData.csv";
	UFUNCTION(BlueprintCallable, Category = "Tracker Data Table")
	void BPSaveDataTable();
	long int Counter = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
