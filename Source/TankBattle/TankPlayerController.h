// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"
#define OUT
/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATank* GetTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	UPROPERTY(EditAnywhere)
		float Xpos = 0.5;
	UPROPERTY(EditAnywhere)
		float Ypos = 0.333;
	UPROPERTY(EditAnywhere)
		float AimingRange = 10000000;

 private:
	 //start the tank by moving the barrel towards the cross hair
	void AimTowardCrossHair();
	bool GetAimHitDirection(FVector & inVector, FVector & CameraPos) const;
	//get the aiming world direction
	bool GetHitLocation(FHitResult& HitRes) const;
};
