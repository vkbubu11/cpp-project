// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerUpActor.generated.h"

UCLASS()
class BASICCODEPROJECT_API ASPowerUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerUpActor();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
	float PowerupsInterval;

	UPROPERTY(EditDefaultsOnly,Category="Powerups")
	int32 TotalNrOfTicks;

	FTimerHandle TimerHandle_PowerupTicks;

	int32 TicksProcessed;

	UFUNCTION()
	void OnTickPowerup();

	UPROPERTY(ReplicatedUsing=OnRep_PowerupActive)
	bool bIsPowerupActive;

	UFUNCTION()
	void OnRep_PowerupActive();

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnPowerupStateChange(bool bNewIsActive);

public:	

	void ActivatePowerup(AActor* ActiveFor);

	UFUNCTION(BlueprintImplementableEvent,Category="Powerups")
	void OnActivated(AActor* ActiveFor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnPowerupTicked();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnExpired();
};
