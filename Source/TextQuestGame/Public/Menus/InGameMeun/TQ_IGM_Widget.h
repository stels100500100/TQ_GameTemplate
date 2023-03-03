// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TQ_Widgets/TQ_Base_IG_Menu.h"
#include "TQ_IGM_Widget.generated.h"

class UButton;

UCLASS()
class TEXTQUESTGAME_API UTQ_IGM_Widget : public UTQ_Base_IG_Menu
{
	GENERATED_BODY()
public:
		virtual void NativeOnInitialized() override;

private:

	UFUNCTION()
		void SaveGame();

	UPROPERTY(meta = (BindWidget))
		UButton* SaveGameButton;
	

};
