// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TQ_GameInstance.h"
#include "TQ_PlayerPawn.h"
#include "TQ_PlayerHUD.h"
#include "TQ_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEXTQUESTGAME_API ATQ_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
		ATQ_GameMode();
	UFUNCTION()
		void OnSaveGame();
	UFUNCTION()
		void OnLoadGame();
	UPROPERTY()
		TSubclassOf<ATQ_PlayerPawn> TQChar;
	UPROPERTY()
		TSubclassOf<ATQ_PlayerHUD> TQHud;
private:

	UTQ_GameInstance* GetGameInstance();
	ATQ_PlayerHUD* GetHud();
	ATQ_PlayerPawn* GetCharacter();
};
