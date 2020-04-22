// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetTank() const
{
	return Cast<ATank>(GetPawn());
}
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto possessedTank = GetTank();
	if (!possessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller C++ class has not found Anything"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Player Controller C++ class found %s"), *(possessedTank->GetName()));
}
void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardCrossHair();
}

void ATankPlayerController::AimTowardCrossHair()
{
	//failed!
	if (!GetTank())
		return;
	FHitResult res;
	if (GetHitLocation(res))
	{
		//UE_LOG(LogTemp, Warning,
		//	L"Aiming at component:%s",*res.GetActor()->GetName());
		GetTank()->AimAt(res.Location);
	}

}
bool ATankPlayerController::GetAimHitDirection(FVector & inVector,FVector& CameraPos) const
{
	//find the dot position on the screen and translate it into world coordinate
	//amd see what we hit
	int32 sizeX, sizeY;
	GetViewportSize(sizeX, sizeY);
	FVector2D ScreenPos = FVector2D(this->Xpos, this->Ypos)*FVector2D(sizeX, sizeY);
	return DeprojectScreenPositionToWorld(ScreenPos.X, ScreenPos.Y, CameraPos, inVector);

}

bool ATankPlayerController::GetHitLocation(FHitResult& HitRes) const
{
	FVector Direction;
	FVector CameraPos;
	GetAimHitDirection(Direction,CameraPos);
	FVector End = CameraPos + Direction * AimingRange;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(GetTank());
	return GetWorld()->LineTraceSingleByChannel(HitRes,
		CameraPos,
		End,
		ECollisionChannel::ECC_Visibility, Params);

}
