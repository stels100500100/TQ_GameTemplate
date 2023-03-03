// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TQ_PlayerController.h"

void ATQ_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	//SetInputMode();
}