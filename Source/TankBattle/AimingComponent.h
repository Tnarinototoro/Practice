// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "AimingComponent.generated.h"
class UTankBarrel; //forward declaration
class UTankTurret;
//holds parameters for barrel
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
	void SetBarrelReferrenceFromOwner(UTankBarrel* BarrelToBeSet);
	void SetTurretreferrenceFromOwner(UTankTurret* TurretTobeSet);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector WorldSpaceAim,float LaunchiSpeed);
	void MoveBarrel(FVector AimDirection);
	

private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
		
};
