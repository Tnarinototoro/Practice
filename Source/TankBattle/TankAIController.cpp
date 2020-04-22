// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto possessedTank = GetAITank();
	if (!possessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller C++ class has not found Anything"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller C++ class found %s"), *(possessedTank->GetName()));
	}
		
	if (GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI finding Player Controller Success"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI finding Player Controller Failed!"));
	}
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
	OurAiTank->AimAt(GetPlayerTank()->GetActorLocation());

}
