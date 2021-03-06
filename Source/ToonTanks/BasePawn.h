// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 400.f;*/

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	void RotateTurret(FVector LookAtTarget);

	void Fire();


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components", meta = (AllowPrivateAccess = true))
		class UCapsuleComponent* CapsulComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components", meta = (AllowPrivateAccess = true))
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsonly, category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, category = "Combat")
		class UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;




};
