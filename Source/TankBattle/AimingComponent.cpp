// Fill out your copyright notice in the Description page of Project Settings.
#include "AimingComponent.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;//do we  really need tick?
	
	// ...
}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UAimingComponent::SetBarrelReferrenceFromOwner(UTankBarrel* BarrelToBeSet)
{
	this->Barrel = BarrelToBeSet;

}

void UAimingComponent::SetTurretreferrenceFromOwner(UTankTurret * TurretTobeSet)
{
	this->Turret = TurretTobeSet;
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAimingComponent::AimAt(FVector WorldSpaceAim,float LaunchiSpeed)
{
	auto OurtankName = (GetOwner()->GetName());
	if (Barrel)
	{
		
		    FVector Barrelpos = Barrel->GetComponentLocation();
			FVector TossV;
			FVector StartLocation = Barrel-> GetSocketLocation(FName("Projectile"));
			FVector AimDirection = TossV.GetUnsafeNormal();
			bool bHaveSolution = UGameplayStatics::SuggestProjectileVelocity(this,
				TossV,
				StartLocation,
				WorldSpaceAim,
				LaunchiSpeed,
				false,
				0,
				0,
				ESuggestProjVelocityTraceOption::DoNotTrace);
			//if we can hit the terget

			if(bHaveSolution)
			{
			
				//move the barrel
				AimDirection = TossV.GetSafeNormal();
				MoveBarrel(AimDirection);
				auto time = GetWorld()->GetTimeSeconds();
				//UE_LOG(LogTemp, Warning,
				//	L"Aimiing at direction %s",
				//	*AimDirection.ToString());
				
			}
			else
			{
				//UE_LOG(LogTemp, Warning,
				//	L"No trace Found!");
				Barrel->Eleate(-1);
				
			}
	}
	else
	{
		return;

	}
}
void UAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrekRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto deltaRotation = AimAsRotator - BarrekRotation;
	Barrel->Eleate(deltaRotation.Pitch);
	//turret yaw
	Turret->RotateTurret(deltaRotation.Yaw);
}

