// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <TQ_Utilitys/TQUtills.h>
#include "TQ_GameInstance.generated.h"

UCLASS()
class TEXTQUESTGAME_API UTQ_GameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
		TSubclassOf<UUserWidget> TQMap;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
		TMap<FName, FSaveMapState> MapState; // gamescreen name , stats of game screen 
		void SetMap(TSubclassOf<UUserWidget> Map) { TQMap = Map; };

};
