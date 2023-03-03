// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <DamageTypes/HungerDamageType.h>
#include "Components/ActorComponent.h"
#include "TQ_HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHungerChanged, float, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEXTQUESTGAME_API UTQ_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTQ_HealthComponent();

	UFUNCTION(BlueprintCallable)
		virtual bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable)
		float GetHungerPercent() const { return Hunger / MaxHunger; }

	UFUNCTION(BlueprintCallable)
		float GetHelth() { return Health; }

	UFUNCTION(BlueprintCallable)
		void OnApplayDamage(float Damage);

	UFUNCTION(BlueprintCallable)
		void OnApplayHunger(float Damage);

	UFUNCTION(BlueprintCallable)
		void SetHEalth(float NewHealth);

	UFUNCTION(BlueprintCallable)
		void SetHLTH(float NewHealth);

	UFUNCTION(BlueprintCallable)
		bool TryToAddHealth(float HealthAmount);

	UFUNCTION(BlueprintCallable)
		void OnTakeAnyDamageHandle(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
		void SetHungerRemove(float NewHunger);

	UFUNCTION(BlueprintCallable)
		bool TryToAddHunger(float HungerAmount);

	UFUNCTION(BlueprintCallable)
		void SetHungerAdd(float NewHunger);

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	FOnHungerChanged OnHungerChanged;

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "TQGame")
		float MaxHealth = 100.0f;
		float Health;

	UPROPERTY(EditAnywhere, Category = "TQGame")
		float MaxHunger = 100.0f;
		float Hunger;
};
