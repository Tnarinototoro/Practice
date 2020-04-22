// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//-1 is max Downward speed,+1 is max up movement
	void Eleate(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere,Category=Setup)
		float MaxDegreesPersecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0;//Todo set in details
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 40;
};
