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
		MoveToActor(PlayerTank, acceptanceRadius);
		auto p = OurAiTank->GetAimingComponent();
		if(p)
		p->AimAt(PlayerTank->GetActorLocation());
		p->Fire();
	}
	else
	{

	}

}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->TankDead.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, L"Tank Dead!!");
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
	GetPawn()->Destroy();
}
