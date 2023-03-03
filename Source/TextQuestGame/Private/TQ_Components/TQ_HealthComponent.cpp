// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Components/TQ_HealthComponent.h"
#include <DamageTypes/DefaultDamageType.h>
#include <DamageTypes/HungerDamageType.h>

UTQ_HealthComponent::UTQ_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UTQ_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHEalth(MaxHealth);
	SetHungerRemove(MaxHunger);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner) {
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UTQ_HealthComponent::OnTakeAnyDamageHandle);
	}
	
}


void UTQ_HealthComponent::OnTakeAnyDamageHandle(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageType->IsA<UDefaultDamageType>())
	{
			OnApplayDamage(Damage);
	}
	if (DamageType->IsA<UHungerDamageType>())
	{
		OnApplayHunger(Damage);
			if (Hunger == 0)
			{
				OnApplayDamage(Damage);
			}
	}

}

void UTQ_HealthComponent::OnApplayDamage(float Damage)
{
	if (Damage < 0.0f || IsDead() || !GetWorld()) return;
	SetHEalth(Health - Damage);


	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void UTQ_HealthComponent::OnApplayHunger(float Damage)
{
	if (Damage < 0.0f || IsDead() || !GetWorld()) return;
	SetHungerRemove(Hunger - Damage);


		if (IsDead())
		{
			OnDeath.Broadcast();
		}
}

void UTQ_HealthComponent::SetHEalth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;


	Health = NextHealth;

	OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool UTQ_HealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead()) return false;

	SetHLTH(Health + HealthAmount);
		return true;
}

void UTQ_HealthComponent::SetHLTH(float NewHealth)
{
	const auto NextHealth = NewHealth;
	const auto HealthDelta = NextHealth + Health;


	Health += NewHealth;

	OnHealthChanged.Broadcast(Health, HealthDelta);
}



void UTQ_HealthComponent::SetHungerRemove(float NewHunger)
{
	const auto NextHunger = FMath::Clamp(NewHunger, 0.0f, MaxHunger);
	const auto HungerDelta = NextHunger - Hunger;


	Hunger = NextHunger;

	OnHungerChanged.Broadcast(Hunger, HungerDelta);
}

bool UTQ_HealthComponent::TryToAddHunger(float HungerAmount)
{
	if (IsDead()) return false;

	SetHungerAdd(Hunger + HungerAmount);
		return true;
}

void UTQ_HealthComponent::SetHungerAdd(float NewHunger)
{
	const auto NextHunger = NewHunger;
	const auto HungerDelta = NextHunger + Hunger;


	Hunger += NewHunger;

	OnHungerChanged.Broadcast(Hunger, HungerDelta);
}

