// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


class ASWeapon;
class USHelatComponent;

UCLASS()
class BASICCODEPROJECT_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

	/***/
	class UTextRenderComponent* ChatText;

	/***/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;



	/***/
	UFUNCTION(BlueprintCallable,Category="Chat/Messaging")
	void AttemptToSendChatMessage(const FString& Message);

private:
	/***/
	void SendChatMessage(const FString& Message);
	/***/
	void ClearChatMessage();
	/***/
	UFUNCTION(Server,Reliable,WithValidation)
	void ServerSendChatMessage(const FString& Message);

	/***/
	void ServerSendChatMessage_Implementation(const FString& Message);
	bool ServerSendChatMessage_Validate(const FString& Message);

	/***/
	UFUNCTION()
	void OnRep_CurrentMessage();

	void UpdateChatText();

protected:
	/***/
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Transient,ReplicatedUsing=OnRep_CurrentMessage,Category="Chat/Messaging")
	FString CurrentMessage;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void BeginCrouch();

	void EndCrouch();

	/**/
	UPROPERTY(Replicated)
	ASWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly,Category="Player")
	TSubclassOf<ASWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly,Category="Player")
	FName WeaponAttachSocketName;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	USHealthComponent* HealthComp;

	void StartFire();

	void StopFire();


	UFUNCTION()
	void OnHealthChanged(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(Replicated,BlueprintReadOnly,Category="Player")
	bool bDied;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
