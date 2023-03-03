// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenu/MM_TQ_GameMode.h"
#include "Menus/MainMenu/MM_TQ_Player.h"
#include "Menus/MainMenu/MM_PlayerController.h"
#include "Menus/MainMenu/MM_TQ_HUD.h"


AMM_TQ_GameMode::AMM_TQ_GameMode()
{
	HUDClass = AMM_TQ_HUD::StaticClass();
	DefaultPawnClass = AMM_TQ_Player::StaticClass();
	PlayerControllerClass = AMM_PlayerController::StaticClass();
}