// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/CharacterGeneration/TQ_CharacterGenerationWidget.h"

#include <Animation/WidgetAnimation.h>
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Player/TQ_PlayerPawn.h"
#include <TQ_Components/TQ_Printer.h>


DEFINE_LOG_CATEGORY_STATIC(asd,All,All)

void UTQ_CharacterGenerationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ReadyButton)
	{
		ReadyButton->OnClicked.AddDynamic(this, &UTQ_CharacterGenerationWidget::Ready);
	}
	if (LuckPPButton)
	{
		LuckPPButton->OnClicked.AddDynamic(this, &UTQ_CharacterGenerationWidget::LuckPlus);
	}
	if (LuckMMButton)
	{
		LuckMMButton->OnClicked.AddDynamic(this, &UTQ_CharacterGenerationWidget::LuckMinus);

	}
	if (StrengthPPButton)
	{
		StrengthPPButton->OnClicked.AddDynamic(this, &UTQ_CharacterGenerationWidget::StrengthPlus);

	}
	if (StrengthMMButton)
	{
		StrengthMMButton->OnClicked.AddDynamic(this, &UTQ_CharacterGenerationWidget::StrengthMinus);

	}
	if (IntellegencePPButton)
	{
		IntellegencePPButton->OnClicked.AddDynamic(this, &UTQ_CharacterGenerationWidget::IntellegentcePlus);

	}
	if (IntellegenceMMButton)
	{
		IntellegenceMMButton->OnClicked.AddDynamic(this, &UTQ_CharacterGenerationWidget::IntelegentceMinus);

	}
	if (TextSetterBlock)
	{
		TextSetterBlock->SetAutoWrapText(true);
	}
	PrintTextMessage();
}

void UTQ_CharacterGenerationWidget::CriticalLuck()
{
	if (CriticalLuckTestLimiter == 0 && CriticalLuckTestLimiter<=2)
	{
		PlayAnimationForward(CriticalLuckAnimation);
		ExpiriancePoints = ExpiriancePoints + 5;
		CriticalLuckTestLimiter++;
	}

}

void UTQ_CharacterGenerationWidget::CriticalFailure()
{
	switch (CriticalLuckTestLimiter)
	{
	case 0:FirstCriticalFailScreenWidget = CreateWidget<UUserWidget>(GetWorld(), FirstCriticalFailScreenClass);
		FirstCriticalFailScreenWidget->AddToViewport(3);

		break;
	case 1:SecondCriticalFailScreenWidget = CreateWidget<UUserWidget>(GetWorld(), SecondCriticalFailScreenClass);
		SecondCriticalFailScreenWidget->AddToViewport(3);
		break;
	case 2:ThirdCriticalFailScreenWidget = CreateWidget<UUserWidget>(GetWorld(), ThirdCriticalFailScreenClass);
		ThirdCriticalFailScreenWidget->AddToViewport(3);
		break;
	}
}

bool UTQ_CharacterGenerationWidget::RandomGenirator()
{
	int32 Probobility = FMath::RandRange(0, 10);
	if (CriticalLuckChanse > Probobility)
	{
		return true;
	}
	return false;

}

void UTQ_CharacterGenerationWidget::Ready()
{
	if (Luck + Strength + Intellegentce != 0)
	{
		UE_LOG(asd,Display,TEXT("Ready"))

		if (Luck + Strength + Intellegentce <= 10) UGameplayStatics::OpenLevel(GetWorld(), NormalRootLevel, true);
		if (Luck + Strength + Intellegentce == 15 || Luck + Strength + Intellegentce > 10) UGameplayStatics::OpenLevel(GetWorld(), LukyRootLevel, true);
		if (Luck + Strength + Intellegentce == 20 || Luck + Strength + Intellegentce > 15) UGameplayStatics::OpenLevel(GetWorld(), ExtraLukyRootLevel, true);


	}
	else
	{
		if (RandomGenirator())
		{
			CriticalLuck();
		}
		else
		{
			CriticalFailure();
		}
	}
	

}

void UTQ_CharacterGenerationWidget::PrintTextMessage()
{
	UE_LOG(asd, Display, TEXT("PrintTextMessage start"))

	UTQ_Printer* Printer = NewObject<UTQ_Printer>(this, UTQ_Printer::StaticClass());
	Printer->SetPrinterPropertys(TextSetterBlock, TextMessage);
	Printer->TQPrint();

}
