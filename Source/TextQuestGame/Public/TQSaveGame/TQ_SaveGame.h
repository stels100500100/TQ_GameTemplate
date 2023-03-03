// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include <TQ_Utilitys/TQUtills.h>
#include <TQ_Components/Inventory/TQ_InventoryStruct.h>
#include "TQ_SaveGame.generated.h"


UCLASS()
class TEXTQUESTGAME_API UTQ_SaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UTQ_SaveGame();

	// propertys to save/load
	UPROPERTY(EditAnywhere)
		int32 SavedIntellegents;
	UPROPERTY(EditAnywhere)
		int32 SavedLuck;
	UPROPERTY(EditAnywhere)
		int32 SavedStrength;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> SavedLevelScreen;

	UPROPERTY(EditAnywhere)
		TMap <FName,FSaveMapState> TQSavedMapStates;
	UPROPERTY(EditAnywhere)
		TArray <FString> SavedEffects;
	UPROPERTY(EditAnywhere)
		int32 SavedSlot1;
	UPROPERTY(EditAnywhere)
		int32 SavedSlot2;
	UPROPERTY(EditAnywhere)
		int32 SavedSlot3;
	UPROPERTY(EditAnywhere)
		int32 SavedSlot4;
	UPROPERTY(EditAnywhere)
		float HealthSaved;
};
