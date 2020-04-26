// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"
void UTrack::SetThrottleRequest(float throttle)
{
	UE_LOG(LogTemp, Warning, L"Throttle input!");
	throttle = FMath::Clamp<float>(throttle, -1, 1);
	auto ForceApplied =GetForwardVector()* throttle*TrackMaxForce;
	auto Forcelocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, Forcelocation);

}

