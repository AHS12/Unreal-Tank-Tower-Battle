// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()


public:

	// Sets default values for this pawn's properties
	ATower();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere, category = "Combat")
		float FireRange = 300.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
	bool CheckInFireRange();

};
