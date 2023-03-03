// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/TQ_LevelScreenWidget.h"
#include "Components/Button.h"
#include <TQ_Utilitys/TQ_MovementStruct.h>
#include <Components/VerticalBox.h>
#include <Kismet\GameplayStatics.h>
#include "Sound/SoundCue.h"
#include "TQ_Utilitys/TQUtills.h"

DEFINE_LOG_CATEGORY_STATIC(TQLevelScreen, All, All);

void UTQ_LevelScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoForwardButton)
	{

		GoForwardButton->OnClicked.AddDynamic(this, &UTQ_LevelScreenWidget::MoveForward);

	}


	if (GoBackwardButton)
	{

		GoBackwardButton->OnClicked.AddDynamic(this, &UTQ_LevelScreenWidget::MoveBack);
	}


	if (GoRightButton)
	{

		GoRightButton->OnClicked.AddDynamic(this, &UTQ_LevelScreenWidget::MoveRight);
	}


	if (GoLeftButton)
	{

		GoLeftButton->OnClicked.AddDynamic(this, &UTQ_LevelScreenWidget::MoveLeft);

	}
	ObsticleStart();
	ObsticleHandling();
}




void UTQ_LevelScreenWidget::ForbidClick(bool g)
{
	if (g)
	{
		IsButtonsActive = true;
		GoForwardButton->SetBackgroundColor(FLinearColor::White);
		GoBackwardButton->SetBackgroundColor(FLinearColor::White);
		GoRightButton->SetBackgroundColor(FLinearColor::White);
		GoLeftButton->SetBackgroundColor(FLinearColor::White);
		WaitButton->SetBackgroundColor(FLinearColor::White);
		ExaminButton->SetBackgroundColor(FLinearColor::White);
	}
	else
	{
		IsButtonsActive = false;
		GoForwardButton->SetBackgroundColor(FLinearColor::Black);
		GoBackwardButton->SetBackgroundColor(FLinearColor::Black);
		GoRightButton->SetBackgroundColor(FLinearColor::Black);
		GoLeftButton->SetBackgroundColor(FLinearColor::Black);
		WaitButton->SetBackgroundColor(FLinearColor::Black);
		ExaminButton->SetBackgroundColor(FLinearColor::Black);
	}

}

void UTQ_LevelScreenWidget::MoveForward()
{
	if (TQBV_EventSystems.WaitingEvent.WaitImageSequence.Num() != 0)
	{
		if (TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].bWantDerectioninfluence)  
		{
			TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].Speech;
			EventHandling(TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].WhatToDo);
		}
		else {
			TQBV_EventSystems.NarrationEvent.GoToNextMap = Movement.ForwardScreen;
			Travel(TQBV_EventSystems.NarrationEvent.GoToNextMap);
		}
	}
	else
	{
		TQBV_EventSystems.NarrationEvent.GoToNextMap = Movement.ForwardScreen;
		Travel(TQBV_EventSystems.NarrationEvent.GoToNextMap);
	}
}

void UTQ_LevelScreenWidget::MoveBack()
{
	if (TQBV_EventSystems.WaitingEvent.WaitImageSequence.Num() != 0)
	{
		if (TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].bWantDerectioninfluence) 
		{
			TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].Speech;
			EventHandling(TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].WhatToDo);
		}
		else
		{
			TQBV_EventSystems.NarrationEvent.GoToNextMap = Movement.BackwardScreen;
			Travel(TQBV_EventSystems.NarrationEvent.GoToNextMap);
		}
	}
	else
	{
		TQBV_EventSystems.NarrationEvent.GoToNextMap = Movement.BackwardScreen;
		Travel(TQBV_EventSystems.NarrationEvent.GoToNextMap);
	}
}

void UTQ_LevelScreenWidget::MoveRight()
{
	if (TQBV_EventSystems.WaitingEvent.WaitImageSequence.Num() != 0)
	{
		if (TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].bWantDerectioninfluence) 
		{
			TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].Speech;
			EventHandling(TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].WhatToDo);
		}
		else
		{
			TQBV_EventSystems.NarrationEvent.GoToNextMap = Movement.RightScreen;
			Travel(TQBV_EventSystems.NarrationEvent.GoToNextMap);
		}
	}
	else
	{
		TQBV_EventSystems.NarrationEvent.GoToNextMap = Movement.RightScreen;
		Travel(TQBV_EventSystems.NarrationEvent.GoToNextMap);
	}
}

void UTQ_LevelScreenWidget::MoveLeft()
{
	if (TQBV_EventSystems.WaitingEvent.WaitImageSequence.Num() != 0)
	{
		if (TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].bWantDerectioninfluence)  
		{
			TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].Speech;
			EventHandling(TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].WhatToDo);
		}
		else {
			TQBV_EventSystems.NarrationEvent.GoToNextMap = Movement.LeftScreen;
			Travel(TQBV_EventSystems.NarrationEvent.GoToNextMap);
		}
	}
	else {
		TQBV_EventSystems.NarrationEvent.GoToNextMap = Movement.LeftScreen;
		Travel(TQBV_EventSystems.NarrationEvent.GoToNextMap);
	}
}

void UTQ_LevelScreenWidget::ObsticleStart()
{
	if (TQBV_EventSystems.HiddenObjectHandlingParams.TreatAsObsticle)
	{
		Movement.ObsticleLeft = true;
		Movement.ObsticleRight = true;
		Movement.ObsticleForward = true;
		Movement.ObsticleBackward = true;
	}
}

void UTQ_LevelScreenWidget::ObsticleHandling()
{						
	if (Movement.ObsticleForward)
	{
		GoForwardButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		GoForwardButton->SetVisibility(ESlateVisibility::Visible);
	}
	if (Movement.ObsticleBackward)
	{
		GoBackwardButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		GoBackwardButton->SetVisibility(ESlateVisibility::Visible);
	}
	if (Movement.ObsticleRight)
	{
		GoRightButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		GoRightButton->SetVisibility(ESlateVisibility::Visible);
	}
	if (Movement.ObsticleLeft)
	{
		GoLeftButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		GoLeftButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UTQ_LevelScreenWidget::DestroyItem()
{
	UE_LOG(TQLevelScreen,Display,TEXT(" TQLevelScreen DestroyItem"))
	Movement.ObsticleLeft = false;
	Movement.ObsticleRight = false;
	Movement.ObsticleForward = false;
	Movement.ObsticleBackward = false;
	ObsticleHandling();
}