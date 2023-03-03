// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TQ_Components/TQ_WalkmanComponent.h"
#include "MM_TQ_Player.generated.h"

class UTQ_WalkmanComponent;

UCLASS()
class TEXTQUESTGAME_API AMM_TQ_Player : public APawn
{
	GENERATED_BODY()

public:
		AMM_TQ_Player();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTQ_WalkmanComponent* WalkManComponent;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
