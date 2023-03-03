// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenu/MM_PlayerController.h"

void AMM_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}