// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MM_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEXTQUESTGAME_API AMM_PlayerController : public APlayerController
{
	GENERATED_BODY()
private:
		virtual void BeginPlay() override;
};
