// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/InGameMeun/TQ_IGM_Widget.h"
#include <Components/Button.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Player/TQ_GameMode.h>

void UTQ_IGM_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (SaveGameButton)
	{
		SaveGameButton->OnClicked.AddDynamic(this, &UTQ_IGM_Widget::SaveGame);
	}
	
}

void UTQ_IGM_Widget::SaveGame()
{
	const auto Mode = Cast<ATQ_GameMode>(GetWorld()->GetAuthGameMode());
	Mode->OnSaveGame();
}

