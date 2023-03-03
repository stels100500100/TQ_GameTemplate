// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenu/MM_TQ_Widget.h"
#include <Components/Button.h>
#include <Menus/MainMenu/MM_TQ_GameMode.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>




void UMM_TQ_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddDynamic(this, &UMM_TQ_Widget::NewGame);
	}

	if (ContinueGameButton)
	{
		ContinueGameButton->OnClicked.AddDynamic(this, &UMM_TQ_Widget::ContinueGame);

	}

	if (GameOptionsButton)
	{
		GameOptionsButton->OnClicked.AddDynamic(this, &UMM_TQ_Widget::GameOptions);

	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UMM_TQ_Widget::QuitGame);

	}

}

void UMM_TQ_Widget::NewGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), NewGameLevelName, true);
}

void UMM_TQ_Widget::ContinueGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), GameLevelName, true);
}

void UMM_TQ_Widget::GameOptions()
{

}

void UMM_TQ_Widget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
