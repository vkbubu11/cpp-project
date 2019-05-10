// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerUpActor.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	PowerupsInterval = 0.0f;
	TotalNrOfTicks = 0;
	bIsPowerupActive = false;
	SetReplicates(true);
}

void ASPowerUpActor::OnTickPowerup()
{
	TicksProcessed++;
	OnPowerupTicked();

	if (TicksProcessed >= TotalNrOfTicks) {
		OnExpired();
		bIsPowerupActive = false;
		OnRep_PowerupActive();
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTicks);
	}
}

void ASPowerUpActor::OnRep_PowerupActive()
{
	OnPowerupStateChange(bIsPowerupActive);
}

void ASPowerUpActor::ActivatePowerup(AActor* ActiveFor)
{
	OnActivated(ActiveFor);
	bIsPowerupActive = true;
	OnRep_PowerupActive();

	if (PowerupsInterval > 0) {
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTicks, this, &ASPowerUpActor::OnTickPowerup, PowerupsInterval, true);
	}
	else {
		OnTickPowerup();
	}
}

void ASPowerUpActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASPowerUpActor, bIsPowerupActive);
}
