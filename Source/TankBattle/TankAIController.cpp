// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
ATank * ATankAIController::GetAITank()const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerTank);
}

void ATankAIController::Tick(float deltaTime)
{
	ATank* OurAiTank = this->GetAITank();
	ATank* PlayerTank = GetPlayerTank();
	if (OurAiTank&&PlayerTank)
	{
		OurAiTank->AimAt(PlayerTank->GetActorLocation());
		//OurAiTank->Fire();
	}
	else
	{

	}

}
