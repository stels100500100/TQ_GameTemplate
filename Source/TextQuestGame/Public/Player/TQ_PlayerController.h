// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TQ_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEXTQUESTGAME_API ATQ_PlayerController : public APlayerController
{
	GENERATED_BODY()
		void BeginPlay() override;

};
