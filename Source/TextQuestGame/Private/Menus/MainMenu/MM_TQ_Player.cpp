// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenu/MM_TQ_Player.h"
#include "TQ_Components/TQ_WalkmanComponent.h"

// Sets default values
AMM_TQ_Player::AMM_TQ_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMM_TQ_Player::BeginPlay()
{
	Super::BeginPlay();
	if (!WalkManComponent) return;
	WalkManComponent = CreateDefaultSubobject<UTQ_WalkmanComponent>("WalkManComponent");
}


// Called to bind functionality to input
void AMM_TQ_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
