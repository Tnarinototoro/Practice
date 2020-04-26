// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include"AimingComponent.h"
#include "Tank.generated.h"
UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UAimingComponent* TanAimingCompo = nullptr;

public:	
	// Called every frame
	void AimAt(FVector HitLocation);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable,Category=Setup)
	void SetBarrelReferrence(UTankBarrel* BarrelFromOutSide);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretRefferrence(UTankTurret* TurretFromOutside);

	UFUNCTION(BlueprintCallable)
		void Fire();

private:
	UTankBarrel* localBarrel = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000; //starting speed 1000m/s

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjecTileBluePrint;
	UPROPERTY(EditDefaultsOnly , Category = Firing)
	float ReloadTimeSeconds = 3;

	double LastFireTime=0;
};
