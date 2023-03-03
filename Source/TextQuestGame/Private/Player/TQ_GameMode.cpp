// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TQ_GameMode.h"
#include "Player/TQ_PlayerPawn.h"
#include "Player/TQ_PlayerHUD.h"
#include "Player/TQ_PlayerController.h"
#include "TQ_Components/TQ_HealthComponent.h"
#include "TQ_Components/TQ_InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include <TQ_Utilitys/TQUtills.h>
#include "TQSaveGame/TQ_SaveGame.h"

DEFINE_LOG_CATEGORY_STATIC(ModLog, All, All)

ATQ_GameMode::ATQ_GameMode()
{
	DefaultPawnClass = ATQ_PlayerPawn::StaticClass();
	
	HUDClass = ATQ_PlayerHUD::StaticClass();

	PlayerControllerClass = ATQ_PlayerController::StaticClass();
}

UTQ_GameInstance* ATQ_GameMode::GetGameInstance()
{
	const auto TQGameInst = Cast<UTQ_GameInstance>(GetWorld()->GetGameInstance());

	return TQGameInst;
}

ATQ_PlayerHUD* ATQ_GameMode::GetHud()
{
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	return HUD;
}
ATQ_PlayerPawn* ATQ_GameMode::GetCharacter()
{
	const auto Character = Cast<ATQ_PlayerPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	return Character;
}

void ATQ_GameMode::OnSaveGame()
{
	UTQ_SaveGame* SaveGameInstance = Cast<UTQ_SaveGame>(UGameplayStatics::CreateSaveGameObject(UTQ_SaveGame::StaticClass()));
	SaveGameInstance->SavedLuck = GetCharacter()->GetLuck();
	SaveGameInstance->SavedIntellegents = GetCharacter()->GetIntelegents();
	SaveGameInstance->SavedStrength = GetCharacter()->GetStrength();
	SaveGameInstance->SavedEffects = GetCharacter()->GetEffects();
	SaveGameInstance->HealthSaved = GetCharacter()->FindComponentByClass<UTQ_HealthComponent>()->GetHelth();
	SaveGameInstance->SavedSlot1 = GetCharacter()->FindComponentByClass<UTQ_InventoryComponent>()->slot1;
	SaveGameInstance->SavedSlot2 = GetCharacter()->FindComponentByClass<UTQ_InventoryComponent>()->slot2;
	SaveGameInstance->SavedSlot3 = GetCharacter()->FindComponentByClass<UTQ_InventoryComponent>()->slot3;
	SaveGameInstance->SavedSlot4 = GetCharacter()->FindComponentByClass<UTQ_InventoryComponent>()->slot4;

	SaveGameInstance->SavedLevelScreen = GetHud()->GetScreenLevelMap();

	SaveGameInstance->TQSavedMapStates = GetGameInstance()->MapState;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("FirstSlot"), 0);
	UE_LOG(ModLog, Display, TEXT("GameSaved"));
}

void ATQ_GameMode::OnLoadGame()
{
	UTQ_SaveGame* SaveGameInstance = Cast<UTQ_SaveGame>(UGameplayStatics::CreateSaveGameObject(UTQ_SaveGame::StaticClass()));
	SaveGameInstance = Cast<UTQ_SaveGame>(UGameplayStatics::LoadGameFromSlot("FirstSlot", 0));

	GetCharacter()->SetLuck(SaveGameInstance->SavedLuck);
	GetCharacter()->SetStrength(SaveGameInstance->SavedStrength);
	GetCharacter()->SetIntellegents(SaveGameInstance->SavedIntellegents);
	GetCharacter()->SetEffects(SaveGameInstance->SavedEffects);

	GetCharacter()->FindComponentByClass<UTQ_InventoryComponent>()->SetSlots(SaveGameInstance->SavedSlot1, SaveGameInstance->SavedSlot2, SaveGameInstance->SavedSlot3, SaveGameInstance->SavedSlot4);

	GetCharacter()->FindComponentByClass<UTQ_HealthComponent>()->SetHEalth(SaveGameInstance->HealthSaved);
	GetHud()->SetScreenLevelMap(SaveGameInstance->SavedLevelScreen);
	GetHud()->ReDrawTQMap(SaveGameInstance->SavedLevelScreen);
	GetGameInstance()->MapState = SaveGameInstance->TQSavedMapStates;
	//SaveGameInstance->TQSavedMapStates. = GetGameInstance()->MapState;
}