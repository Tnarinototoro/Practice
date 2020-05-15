// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "UObject/ConstructorHelpers.h"

void UTankBarrel::Eleate(float RelativeSpeed)
{
	//Clamp Relative Speed from -1 to +1;
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPersecond*GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation=FMath::Clamp<float>(RawNewElevation,MinElevationDegrees,MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation,0,0));
}

UTankBarrel::UTankBarrel()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("StaticMesh'/Game/Tank/tank_fbx_Barrel.tank_fbx_Barrel'"));
	if (Asset.Succeeded())
	{
		this->SetStaticMesh(Asset.Object);

		UE_LOG(LogTemp, Warning,
			L"Barrel mesh found!!!");
	}
}
