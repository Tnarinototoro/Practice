// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "UObject/UObjectHash.h"
#include "Camera/CameraComponent.h"

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
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController.h:Player Controller C++ class has not found Anything"));
	}

}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardCrossHair();
	UInputComponent* input = FindComponentByClass<UInputComponent>();
	if (!input)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController.h:inputComponent not Found!"));
	}
}
void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController.h:PlayerTank Dead!"));
	//StartSpectatingOnly();
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATank::StaticClass(), Actors);
	FString name = GetTank()->GetName();
	GetTank()->Destroy();
	this->SetPawn(NULL);
	static bool dead = false;
	for (auto m : Actors)
	{
		if (m->GetName() != name)
		{
			
			UE_LOG(LogTemp, Warning, TEXT("Possessing another Tank %s from %s"), *m->GetName(), *m->GetInstigatorController()->GetName());
			if(this->GetPawn()==NULL)
			GetWorld()->GetFirstPlayerController()->Possess(Cast<APawn>(m));

		}
	}
	
}
void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto MyTank = Cast<ATank>(InPawn);
		if (!ensure(MyTank)) { return; }
		MyTank->TankDead.AddUniqueDynamic(this,&ATankPlayerController::OnPossessedTankDeath);
		
	}
}
void ATankPlayerController::AimTowardCrossHair()
{
	//failed!
	if (!GetTank())
		return;
	FHitResult res;
	bool getRes=GetHitLocation(res);
	if (getRes)
	{
		
		auto p = GetTank()->GetAimingComponent();
		if (p)
			p->AimAt(res.Location);
		else
			UE_LOG(LogTemp, Warning, L"TankPlayerController.h:Aiming Component No Found!!")

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
	bool GetRes= GetWorld()->LineTraceSingleByChannel(HitRes,
		CameraPos,
		End,
		ECollisionChannel::ECC_Visibility, Params);
	if (GetRes)
	{
		return true;
	}
	return false;

}
