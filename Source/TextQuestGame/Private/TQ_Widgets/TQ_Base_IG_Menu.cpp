// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/TQ_Base_IG_Menu.h"
#include <Components/Button.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Player/TQ_GameMode.h>

void UTQ_Base_IG_Menu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//if (SaveGameButton)
	//{
	//	SaveGameButton->OnClicked.AddDynamic(this, &UTQ_Base_IG_Menu::SaveGame);
	//}
	if (LoadGameButton)
	{
		LoadGameButton->OnClicked.AddDynamic(this, &UTQ_Base_IG_Menu::LoadGame);
	}
	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UTQ_Base_IG_Menu::QuitGame);

	}
	if (GoToMainMenuButton)
	{
		GoToMainMenuButton->OnClicked.AddDynamic(this, &UTQ_Base_IG_Menu::GoToMainMenue);
	}
}

//void UTQ_Base_IG_Menu::SaveGame()
//{
//	const auto Mode = Cast<ATQ_GameMode>(GetWorld()->GetAuthGameMode());
//	Mode->OnSaveGame();
//}

void UTQ_Base_IG_Menu::LoadGame()
{
	const auto Mode = Cast<ATQ_GameMode>(GetWorld()->GetAuthGameMode());
	Mode->OnLoadGame();
}

void UTQ_Base_IG_Menu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);

}

void UTQ_Base_IG_Menu::GoToMainMenue()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuLevel, true);
}