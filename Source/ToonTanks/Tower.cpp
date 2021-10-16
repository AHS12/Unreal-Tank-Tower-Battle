// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATower::ATower() {

}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	FString Grettings = FString(TEXT("Hello from Tower: ")) + FString(*GetOwner()->GetName());
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Grettings);

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Tank) {
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= FireRange) {
			RotateTurret(Tank->GetActorLocation());
		}
	}

}


