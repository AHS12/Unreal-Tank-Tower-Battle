// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Smoke"));
	TrailParticles->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit)
{
	/*UE_LOG(LogTemp, Warning, TEXT("HIT"));
	UE_LOG(LogTemp, Warning, TEXT("Hit Component %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Other Component %s"), *OtherComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Other Actor %s"), *OtherActor->GetName());*/

	auto ProjectileOwner = GetOwner();

	if (!ProjectileOwner) {
		Destroy();
		return;
	}

	auto ProjectileOwnerInstagator = ProjectileOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileOwnerInstagator, this, DamageTypeClass);
		if (HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());

		}

		Destroy();
	}

	Destroy();

}

