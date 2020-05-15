// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement"));
	if (!ensure(Movement))
		UE_LOG(LogTemp, Warning, L"Projectile.h:Movement not created properly");
	Movement->bAutoActivate = false;


	CollisionMesh =CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	if (!ensure(CollisionMesh))
		UE_LOG(LogTemp, Warning, L"Projectile.h:CollisionMesh not created properly");
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);


	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	if (!ensure(LaunchBlast))
		UE_LOG(LogTemp, Warning, L"Projectile.h:LaunchBlast not created properly");
	LaunchBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	LaunchBlast->bAutoActivate = false;

	HitBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Hit Blast"));
	if (!ensure(HitBlast))
		UE_LOG(LogTemp, Warning, L"Projectile.h:HitBlast not created properly");
	HitBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HitBlast->bAutoActivate = false;

	ExplosionPulse = CreateDefaultSubobject<URadialForceComponent>(FName("ExplostionForce"));
	if (!ensure(ExplosionPulse))
		UE_LOG(LogTemp, Warning, L"Projectile.h:ExplosionPulse not created properly");
	ExplosionPulse->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float speeds)
{
	if (Movement)
	{
		Movement->SetVelocityInLocalSpace(FVector::ForwardVector*speeds);
		//UE_LOG(LogTemp, Warning, TEXT("Forward VEctor %s"), *FVector::ForwardVector.ToString());
		Movement->Activate();
		LaunchBlast->Activate();
		
	}

}
void AProjectile::OntimeExpire()
{
	this->Destroy();
}
void AProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	HitBlast->Activate();
	UE_LOG(LogTemp, Warning, L"Projectile.h:Hit something!!");

	ExplosionPulse->FireImpulse();
	SetRootComponent(HitBlast);
	CollisionMesh->DestroyComponent(); \
	GetWorld()->GetTimerManager().SetTimer(Time, this, &AProjectile::OntimeExpire, DestroyDelay, false);
	UGameplayStatics::ApplyRadialDamageWithFalloff(this, ProjectileDefaultDamage, 2,
		GetActorLocation(),
		50.0f,
		100.0, 0.2, NULL, TArray<AActor*>());
	

}

