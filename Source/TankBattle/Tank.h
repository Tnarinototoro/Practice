// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include"AimingComponent.h"
#include "TankMoveComponent.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeath);


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


public:	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BluePrintCallable, Category = "SetUp")
	UAimingComponent* GetAimingComponent();
	UFUNCTION(BluePrintCallable, Category = "SetUp")
	UTankMoveComponent* GetMoveComponent();
	UPROPERTY(EditDefaultsOnly, Category = "TankStatics")
		float deFaultHealth = 100;
	UFUNCTION(BluePrintPure, Category = "TankStatics")  //pure blueprint is like const 
		float GetCurrentHealthPercent() const;
		FTankDeath TankDead;
private:

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	float CurrentHealth;

};
