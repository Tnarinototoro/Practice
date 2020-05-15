// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "UObject/ConstructorHelpers.h"
void UTankTurret::RotateTurret(float RelativeSpeed)
{
	//the rotate will always rotate to the nearest angle!
	bool reverse = abs(RelativeSpeed) > 180? true : false;
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotateChange = RelativeSpeed * MaxRotationDegreesPersecond*GetWorld()->DeltaTimeSeconds;
	if (reverse)
		RotateChange = (-RotateChange);
	auto Rotation = RelativeRotation.Yaw + RotateChange;
	SetRelativeRotation(FRotator(0, Rotation,0));
}

UTankTurret::UTankTurret()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("StaticMesh'/Game/Tank/tank_fbx_Turret.tank_fbx_Turret'"));
	if (Asset.Succeeded())
	{
		this->SetStaticMesh(Asset.Object);

		UE_LOG(LogTemp, Warning,
			L"Turret mesh found!!!");
	}
}