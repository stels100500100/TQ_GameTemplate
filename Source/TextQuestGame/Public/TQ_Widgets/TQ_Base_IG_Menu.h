// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TQ_Base_IG_Menu.generated.h"

class UButton;
UCLASS()
class TEXTQUESTGAME_API UTQ_Base_IG_Menu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
		void LoadGame();
	UFUNCTION()
		void QuitGame();
	UFUNCTION()
		void GoToMainMenue();

	UPROPERTY(meta = (BindWidget))
		UButton* LoadGameButton;
	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;
	UPROPERTY(meta = (BindWidget))
		UButton* GoToMainMenuButton;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "TQGame")
		FName MainMenuLevel;
};
