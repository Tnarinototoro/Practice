// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMoveComponent.generated.h"
class UTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankMoveComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable)
	void Initialize(UTrack* leftTrackToSet, UTrack* RightTrackToSet);
	UFUNCTION(BlueprintCallable)
	void IntendTurnRight(float Throw);

	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private :
	UTrack* LeftTrack, *RightTrack;
};
