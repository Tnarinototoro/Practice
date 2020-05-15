// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"
#include "SpawnPoint.h"
#include "UObject/ConstructorHelpers.h"
void UTrack::SetThrottleRequest(float throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}
void UTrack::DriveTrack(float  CurrentThrottle)
{
	auto ForceApplied =  CurrentThrottle*TrackMaxForce;
	auto Wheels = GetWheels();
	float ForcePerWheel;
	if(Wheels.Num())
	ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDriveForce(ForcePerWheel);
	}
}
UTrack::UTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("StaticMesh'/Game/Tank/tank_fbx_Track.tank_fbx_Track'"));
	if (Asset.Succeeded())
	{
		this->SetStaticMesh(Asset.Object);

		UE_LOG(LogTemp, Warning,
					L"Track mesh found!!!");
	}
}
TArray<ASprungWheel*> UTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true,Children);
	for (USceneComponent* eachChild : Children)
	{
		auto SpawnedChild = Cast<USpawnPoint>(eachChild);
		if(!SpawnedChild) continue;

		AActor* SpawnedWheel = SpawnedChild->GetSpawnedActor();
		auto SPrungWheel = Cast<ASprungWheel>(SpawnedWheel);
		if (!SPrungWheel) continue;
		ResultArray.Add(SPrungWheel);
	}
	return ResultArray;
}
//void UTrack::ApplySideCorrectionForce()
//{
//	auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
//	auto deltTime = GetWorld()->GetDeltaSeconds();
//	auto CorrectAcc = -SlipSpeed /deltTime  * GetRightVector();
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//	auto CorrectionForce = (TankRoot->GetMass()*CorrectAcc) / 2;
//	TankRoot->AddForce(CorrectionForce);
//}
