// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<ASprungWheel> Asset(TEXT("Blueprint'/Game/Tank/SprungWheel_BP'"));
	if (Asset.Succeeded())
	{
		if (ensure(Asset.Class))
			SprungWheelBP = Asset.Class;

		UE_LOG(LogTemp, Warning,
			L"SprungWheel_BP Loaded!");
	}
	// ...
}


AActor * USpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}

// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SprungWheelBP,GetComponentTransform());
	if (SpawnedActor)
	{
		UE_LOG(LogTemp, Warning,
			L"SprungWheel Spawned Successfully");

	}
	else
		return;


	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

