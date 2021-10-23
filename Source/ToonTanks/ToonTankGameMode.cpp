// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"


void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();

}

void AToonTankGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (ToonTankController) {
		ToonTankController->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnabledTimerHandle;
		FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTankController,
			&AToonTankPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(
			PlayerEnabledTimerHandle,
			PlayerEnabledTimerDelegate,
			StartDelay,
			false
		);
	}
}

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		/*if (Tank->GetTankPlayerController()) {
			Tank->DisableInput(Tank->GetTankPlayerController());
			Tank->GetTankPlayerController()->bShowMouseCursor = false;
		}*/

		if (ToonTankController) {
			ToonTankController->SetPlayerEnabledState(false);
		}

	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) {
		DestroyedTower->HandleDestruction();
	}

}


