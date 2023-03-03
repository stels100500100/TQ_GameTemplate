// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TQ_PlayerPawn.h"

#include "Kismet/GameplayStatics.h"
#include <Engine/Engine.h>
#include "Blueprint/WidgetBlueprintLibrary.h"
#include <TQSaveGame/TQ_SaveGame.h>
#include <TQ_Components/TQ_HealthComponent.h>
#include "TQ_Components/TQ_InventoryComponent.h"
#include <TQ_Components/TQ_WalkmanComponent.h>
#include <TQ_Utilitys/TQUtills.h>
#include <TQ_Widgets/TQ_SpeakerWidget.h>
#include <TQ_Widgets/TQ_BaseLevelWidget.h>

ATQ_PlayerPawn::ATQ_PlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UTQ_HealthComponent>("HealthComponent");
	HealthComponent->OnDeath.AddUObject(this, &ATQ_PlayerPawn::OnDeath);

	InventoryComponent = CreateDefaultSubobject<UTQ_InventoryComponent>("InventoryComponent");
	
	WalkManComponent = CreateDefaultSubobject<UTQ_WalkmanComponent>("WalkManComponent");
}

void ATQ_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);

}

void ATQ_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATQ_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATQ_PlayerPawn::ApplayDamageToSelf(float DamageModifire, TSubclassOf<UDamageType> DamagEvent)
{
	UGameplayStatics::ApplyDamage(this, 1.0f * DamageModifire, nullptr, this, DamagEvent);
}

void ATQ_PlayerPawn::OnDeath()
{
	checkf(DefaultDeath == NULL, TEXT("Death Screen is not seted, check LevelScreen Deathwork grapths"));
	
		DefaultDeath = CreateWidget<UDeathWidget>(GetWorld(), DeathWidget);
		DefaultDeath->AddToViewport(2);
	
	if(DefaultDeath == NULL)
	{

		DDeath = CreateWidget<UDeathWidget>(GetWorld(), DefaultDeathWidget);
		DDeath->AddToViewport(2);
	}
}

void ATQ_PlayerPawn::AddEffect(FString AddIn)
{
	Effects.Add(AddIn);

}

void ATQ_PlayerPawn::RemoveEffect(FString CutIn)
{
	if (Effects.Contains(CutIn))
	{
		Effects.Remove(CutIn);
	}
}