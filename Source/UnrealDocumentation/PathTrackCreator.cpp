// Fill out your copyright notice in the Description page of Project Settings.


#include "PathTrackCreator.h"
#include <Kismet/GameplayStatics.h>
#include "UAVPathTrack.h"

// Sets default values
APathTrackCreator::APathTrackCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
APathTrackCreator::~APathTrackCreator()
{
}

void APathTrackCreator::SaveDataTableToCSV(UDataTable* DataTable)
{
    if (DataTable == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("DataTable is empty."));
        return;
    }
     
    TArray<FName> RowNames = DataTable->GetRowNames();
    const UScriptStruct* RowStruct = DataTable->GetRowStruct();
     
    FString CSVString;
    bool bHeaderWritten = false;
     
    for (TFieldIterator<FProperty> It(RowStruct); It; ++It)
    {
        FProperty* Property = *It;
        if (bHeaderWritten)
        {
            CSVString.AppendChar(',');
        }
        CSVString.Append(Property->GetName());
        bHeaderWritten = true;
    }
    CSVString.AppendChar('\n');
     
    for (const FName& RowName : RowNames)
    {
        uint8* RowData = DataTable->FindRowUnchecked(RowName);
        bool bFirstProperty = true;
         
        for (TFieldIterator<FProperty> It(RowStruct); It; ++It)
        {
            FProperty* Property = *It;
            if (bFirstProperty)
            {
                bFirstProperty = false;
            }
            else
            {
                CSVString.AppendChar(',');
            }

            FString PropertyValue;
            Property->ExportText_InContainer(0, PropertyValue, RowData, nullptr, nullptr, PPF_None);
            CSVString.Append(PropertyValue);
        }
        CSVString.AppendChar('\n');
    }
     
    FString DirectoryPath = FPaths::ProjectSavedDir() / TEXT("TrackerData/");
    FString FilePath = DirectoryPath / TEXT("InitialTestDataTable.csv");
     
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DirectoryExists(*DirectoryPath))
    {
        PlatformFile.CreateDirectoryTree(*DirectoryPath);
    }
     
    if (FFileHelper::SaveStringToFile(CSVString, *FilePath))
    {
        UE_LOG(LogTemp, Log, TEXT("DataTablesaved  %s"), *FilePath);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("DataTable issue occured %s"), *FilePath);
    }
}
// Called when the game starts or when spawned
void APathTrackCreator::BeginPlay()
{
	Super::BeginPlay(); 
}
void APathTrackCreator::AddRowToTable(double Longitude, double Latitude, double Height)
{
	// Create a new row
	FAircraftRawData* newRow = new FAircraftRawData();
	newRow->Longitude = Longitude;
	newRow->Latitude = Latitude;
	newRow->Height = Height;
	// Add the row to the data table
	RecorderDataTable->AddRow(FName("Row1"), *newRow);
}
void APathTrackCreator::BPSaveDataTable()
{
	SaveDataTableToCSV(RecorderDataTable);
}
// Called every frame
void APathTrackCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

