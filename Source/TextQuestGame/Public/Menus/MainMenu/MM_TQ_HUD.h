// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MM_TQ_HUD.generated.h"

/**
 * 
 */
UCLASS()
class TEXTQUESTGAME_API AMM_TQ_HUD : public AHUD
{
	GENERATED_BODY()
private:

		virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MenuToDisplay;
		UUserWidget* MenueToCreate;
};
