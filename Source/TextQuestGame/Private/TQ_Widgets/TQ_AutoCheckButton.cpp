// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/TQ_AutoCheckButton.h"
#include <TQ_Utilitys/TQUtills.h>
#include <Kismet\GameplayStatics.h>
#include <Engine/Engine.h>
#include <Player/TQ_PlayerPawn.h>

UTQ_AutoCheckButton::UTQ_AutoCheckButton(const FObjectInitializer& ObjectInit)
{
	OnClicked.AddDynamic(this, &UTQ_AutoCheckButton::GiveResoult);

}


bool UTQ_AutoCheckButton::CheckStats(EStatusAutoCheck WhatToCheck)
{
	const auto Character = Cast<ATQ_PlayerPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	switch (WhatToCheck)
	{
	case EStatusAutoCheck::Luck:
		if (Character->GetLuck() >= StatPihvaRequirement) return FinalResault = true;
		if (Character->GetLuck() < StatPihvaRequirement) return FinalResault = false;
		break;

	case EStatusAutoCheck::Strength:
		if (Character->GetStrength() >= StatPihvaRequirement) return FinalResault = true;
		if (Character->GetStrength() < StatPihvaRequirement) return FinalResault = false;
		break;

	case EStatusAutoCheck::Intellegents:
		if (Character->GetIntelegents() >= StatPihvaRequirement) return FinalResault = true;
		if (Character->GetIntelegents() < StatPihvaRequirement) return FinalResault = false;
		break;

	default:
		return false;
		break;
	}
	return FinalResault;
}


void UTQ_AutoCheckButton::GiveResoult()
{
	const auto Character = Cast<ATQ_PlayerPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Character->Effects.Contains(EffectToCheck))
	{
		OnEffectAutoChecked.Broadcast(EffectToCheck);
		OnStatusAutoChecked.Broadcast(EffectDescription);
	}
	else
	{
		CheckStats(SelectionVar);
		FinalResault ? OnStatusAutoChecked.Broadcast(MessageOnSuccess) : OnStatusAutoChecked.Broadcast(MessageOnFail);
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Black, TEXT("Worked: %d , FinalResault"));
	}
}

