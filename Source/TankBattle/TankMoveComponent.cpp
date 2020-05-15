// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMoveComponent.h"
#include "Track.h"
void UTankMoveComponent::IntendMoveForward(float thro)
{
	if (!LeftTrack || !RightTrack) {
		return;

	}
	LeftTrack->SetThrottleRequest(thro);
	RightTrack->SetThrottleRequest(thro);
}

void UTankMoveComponent::Initialize(UTrack * leftTrackToSet, UTrack * RightTrackToSet)
{
	this->LeftTrack = leftTrackToSet;
	this->RightTrack = RightTrackToSet;
}

void UTankMoveComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) {
		return;}
	LeftTrack->SetThrottleRequest(Throw);
	RightTrack->SetThrottleRequest(-Throw);
}

void UTankMoveComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIVelocity = MoveVelocity.GetSafeNormal();
	FVector TankFacing=GetOwner()->GetActorForwardVector().GetSafeNormal();
	float Throttle = FVector::DotProduct(AIVelocity,TankFacing);
	//set intendforward parameter
	IntendMoveForward(Throttle);
	float ThrottleX = FVector::CrossProduct(TankFacing, AIVelocity).Z;
	//set right instruction
	IntendTurnRight(ThrottleX);
}
