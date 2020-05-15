// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = this->deFaultHealth;
	
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
UAimingComponent*  ATank::GetAimingComponent()
{
	
	return FindComponentByClass<UAimingComponent>();
}

UTankMoveComponent * ATank::GetMoveComponent()
{
	return FindComponentByClass<UTankMoveComponent>();
}

float ATank::GetCurrentHealthPercent() const
{
	return (float)CurrentHealth/(float)deFaultHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		TankDead.Broadcast();
		UE_LOG(LogTemp, Warning, L"Tank dead");
	}
	return DamageToApply;
}

