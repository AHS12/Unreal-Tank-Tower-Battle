// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"
#define OUT

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();

}

void AToonTankGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

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

int32 AToonTankGameMode::GetTargetTowerCount()
{
	TArray <AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), OUT Towers);
	return Towers.Num();
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
		GameOver(false);

	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) {
		DestroyedTower->HandleDestruction();
		TargetTowers--;

		if (TargetTowers == 0) {
			GameOver(true);
		}


	}

}


