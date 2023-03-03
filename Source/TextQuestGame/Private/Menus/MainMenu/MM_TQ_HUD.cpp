// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenu/MM_TQ_HUD.h"

void AMM_TQ_HUD::BeginPlay()
{
	Super::BeginPlay();

	MenueToCreate = CreateWidget<UUserWidget>(GetOwningPlayerController(), MenuToDisplay);
	MenueToCreate->AddToViewport(0);

}