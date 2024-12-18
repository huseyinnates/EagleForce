// Fill out your copyright notice in the Description page of Project Settings.


#include "UAVPathTrack.h"

// Sets default values
AUAVPathTrack::AUAVPathTrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Initialize the track
	SplineTrack = CreateDefaultSubobject<USplineComponent>(TEXT("SplineTrack"));
	// This lets us visualize the spline in Play mode
	SplineTrack->SetDrawDebug(true);
	// Set the color of the spline
	SplineTrack->SetUnselectedSplineSegmentColor(FLinearColor(1.f, 0.f, 0.f));
}

void AUAVPathTrack::LoadSplineTrackPoints()
{
    if (this->AircraftsRawDataTable != nullptr && this->CesiumGeoreference != nullptr)
    {
        int32 PointIndex = 0;
        for (auto& row : this->AircraftsRawDataTable->GetRowMap())
        {
            FAircraftRawData* Point = (FAircraftRawData*)row.Value;
            // Get row data point in lat/long/alt and transform it into UE4 points
            double PointLatitude = Point->Latitude;
            double PointLongitude = Point->Longitude;
            double PointHeight = Point->Height;

            // Compute the position in UE coordinates
            FVector UECoords = this->CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(PointLongitude, PointLatitude, PointHeight));
            FVector SplinePointPosition = FVector(UECoords.X, UECoords.Y, UECoords.Z);
            this->SplineTrack->AddSplinePointAtIndex(SplinePointPosition, PointIndex, ESplineCoordinateSpace::World, false);

            // Get the up vector at the position to orient the aircraft
            const CesiumGeospatial::Ellipsoid& Ellipsoid = CesiumGeospatial::Ellipsoid::WGS84;
            glm::dvec3 upVector = Ellipsoid.geodeticSurfaceNormal(CesiumGeospatial::Cartographic(FMath::DegreesToRadians(PointLongitude), FMath::DegreesToRadians(PointLatitude), FMath::DegreesToRadians(PointHeight)));

            // Compute the up vector at each point to correctly orient the plane
            glm::dvec4 ecefUp(upVector, 0.0);
            const GeoTransforms& geoTransforms = this->CesiumGeoreference->GetGeoTransforms();
            const glm::dmat4& ecefToUnreal = geoTransforms.GetEllipsoidCenteredToAbsoluteUnrealWorldTransform();
            glm::dvec4 unrealUp = ecefToUnreal * ecefUp;
            this->SplineTrack->SetUpVectorAtSplinePoint(PointIndex, FVector(unrealUp.x, unrealUp.y, unrealUp.z), ESplineCoordinateSpace::World, false);

            PointIndex++;
        }
        this->SplineTrack->UpdateSpline();
    }
}
// Called when the game starts or when spawned
void AUAVPathTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUAVPathTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

