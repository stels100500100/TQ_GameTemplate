// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TQ_PlayerHUD.h"
#include <Blueprint/UserWidget.h>
#include <TQ_Widgets/BattleWidgets/TQ_AttackCellWidget.h>
#include "Player/TQ_PlayerHUDWidget.h"

void ATQ_PlayerHUD::DrawHUD()
{
	Super::DrawHUD();

}

void ATQ_PlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	ReDrawHUD();
	ReDrawTQMap(TQMap);

}

void ATQ_PlayerHUD::AskToPrintText()
{
	UI->SetEHRTransfer(EHRMessage);
	UI->DrawMessage();
}

void ATQ_PlayerHUD::SkipResponce()
{
	UI->MRGminus();
}

void ATQ_PlayerHUD::SetAttackMessage()
{
	UI->MakeACW(ActionPointsScore, Pronouncement);
}

void ATQ_PlayerHUD::UnsetAttackMessage()
{
	UI->UNMakeACW();
}

void ATQ_PlayerHUD::FromVictory()
{
	UI->DestroyAllContent();
}

void ATQ_PlayerHUD::ReDrawHUD()
{
	UI = CreateWidget<UTQ_PlayerHUDWidget>(GetOwningPlayerController(), TQUserInterface);
	UI->AddToViewport(1);

}
void ATQ_PlayerHUD::ReDrawTQMap(TSubclassOf<UUserWidget> Map)
{
	ItSelfMap = CreateWidget<UUserWidget>(GetOwningPlayerController(), Map);
	ItSelfMap->AddToViewport(0);
}