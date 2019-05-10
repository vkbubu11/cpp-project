// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "MyProjectileSWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BASICCODEPROJECT_API AMyProjectileSWeapon : public ASWeapon
{
	GENERATED_BODY()

protected:
	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly,Category="ProjectileWeapon")
	TSubclassOf<AActor> ProjectileClass;
	
};
