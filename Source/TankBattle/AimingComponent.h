// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "AimingComponent.generated.h"
//holds parameters for barrel
UENUM()
enum class FiringState : uint8
{
	Reloading=0,
	ReadyToFire,
	OutofAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReferrenceFromOwner(UTankBarrel* BarrelToBeSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretreferrenceFromOwner(UTankTurret* TurretTobeSet);
	

	void AimAt(FVector WorldSpaceAim);
	void MoveBarrel(FVector AimDirection);
	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Fire();
	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	int AmmoCurrent = 20;
	UPROPERTY(BlueprintReadWrite, Category ="Firing")
	FiringState AimingState;
	UPROPERTY(BlueprintReadWrite, Category = Setup)
		TSubclassOf<AProjectile> ProjecTileBluePrint;
private:

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000; //starting speed 1000m/s

	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeSeconds = 2;

	double LastFireTime = 0;

	
};
