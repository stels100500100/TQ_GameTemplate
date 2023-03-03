// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Components/TQ_Printer.h"
#include "Components/TextBlock.h"

UTQ_Printer::UTQ_Printer() : Super()
{
	//Delegate.BindUFunction(this, "TQPrint", Character);
}


void UTQ_Printer::TQPrint()
{
	if (TextMessage.Len() != 0)
	{
		if (CharCount <= TextMessage.Len())
		{
			NextChar = TextMessage.GetCharArray()[CharCount];
			CurrentText = CurrentText + NextChar;
			ConvertedText = ConvertedText.FromString(CurrentText);
			CharCount++;
			TextSetterBlock->SetText(ConvertedText);
			GetWorld()->GetTimerManager().SetTimer(Delay, this, &UTQ_Printer::TQPrint, TextPrintingDelay, false);
			//GetWorld()->GetTimerManager().SetTimer(Delay, Delegate, TextPrintingDelay, false);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(Delay);
			CharCount = 0;
		}
	}
	else
	{
		TextSetterBlock->SetText(ConvertedText.FromString(Default));
	}


};

UTQ_Printer::~UTQ_Printer()
{

}