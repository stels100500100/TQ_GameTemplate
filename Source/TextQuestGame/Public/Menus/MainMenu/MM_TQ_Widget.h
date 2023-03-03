// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "Blueprint/UserWidget.h"
#include "MM_TQ_Widget.generated.h"

class UButton;
class USoundCue;

UCLASS()
class TEXTQUESTGAME_API UMM_TQ_Widget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* ContinueGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* GameOptionsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;

	UPROPERTY(EditAnywhere, Category = "TQGame")
		FName NewGameLevelName;
	UPROPERTY(EditAnywhere, Category = "TQGame")
		FName GameLevelName;
private:
	UFUNCTION()
		void NewGame();
	UFUNCTION()
		void ContinueGame();

	UFUNCTION()
		void GameOptions();
	UFUNCTION()
		void QuitGame();

};
