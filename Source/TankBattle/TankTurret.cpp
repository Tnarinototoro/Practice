// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
void UTankTurret::RotateTurret(float RelativeSpeed)
{
	bool reverse = abs(RelativeSpeed) > 180? true : false;
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotateChange = RelativeSpeed * MaxRotationDegreesPersecond*GetWorld()->DeltaTimeSeconds;
	if (reverse)
		RotateChange = (-RotateChange);
	auto Rotation = RelativeRotation.Yaw + RotateChange;
	SetRelativeRotation(FRotator(0, Rotation,0));
}

