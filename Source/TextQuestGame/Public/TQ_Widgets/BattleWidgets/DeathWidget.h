// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menus/InGameMeun/TQ_IGM_Widget.h"
#include "DeathWidget.generated.h"

class UButton;
class USoundCue;

UCLASS()
class TEXTQUESTGAME_API UDeathWidget : public UTQ_IGM_Widget
{
	GENERATED_BODY()
public:
virtual void NativeOnInitialized() override;
UPROPERTY(BlueprintReadWrite,Transient, meta = (BindWidgetAnim))
UWidgetAnimation* AppearAnim;
private:

	UPROPERTY(EditAnywhere, Category = "TQGame")
		USoundCue* DeathSound;

};
