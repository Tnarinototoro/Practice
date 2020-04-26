// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Track.generated.h"

/**
 * Tank track iis kind of controller to set the maximum driving force,and move the tracks!
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//Sets a throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottleRequest(float throttle);
	
	//MAx force per track
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxForce=4000000;
};
