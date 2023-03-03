// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/TQ_SpeakerWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>

#include <Player/TQ_PlayerPawn.h>
#include <TQ_Utilitys/TQUtills.h>
#include <TQ_Widgets/TQ_BaseLevelWidget.h>
#include <Player/TQ_PlayerHUD.h>
#include <TQ_Components/TQ_Printer.h>


void UTQ_SpeakerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (SkipButton)
	{
		SkipButton->OnClicked.AddDynamic(this, &UTQ_SpeakerWidget::Skip);
	}
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	TextMessage = HUD->GetMessage();
	PrintTextMessage();

	if (TextSetterBlock)
	{
		TextSetterBlock->SetAutoWrapText(true);
	}
}



void UTQ_SpeakerWidget::PrintTextMessage()
{
	UTQ_Printer* Printer = NewObject<UTQ_Printer>(this, UTQ_Printer::StaticClass());
	Printer->SetPrinterPropertys(TextSetterBlock, TextMessage);
	Printer->TQPrint();
}

void UTQ_SpeakerWidget::PrintEffectDisc(FText InEffectHDiscription)
{
	EffectHDiscriptionBlock->SetText(InEffectHDiscription);
}



void UTQ_SpeakerWidget::Skip()
{
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	HUD->SkipResponce();
	HUD->HUDAncver.Broadcast();

	
	RemoveFromParent();

}

void UTQ_SpeakerWidget::MakeRequest()
{
	GetWorld()->GetTimerManager().ClearTimer(Delay);
	SReq.Broadcast();
	RemoveFromParent();
}