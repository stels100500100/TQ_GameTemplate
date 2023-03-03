#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TQ_Printer.generated.h"

class UTextBlock;

UCLASS()
class TEXTQUESTGAME_API UTQ_Printer : public UObject
{
	GENERATED_BODY()

public:
	UTQ_Printer();
	~UTQ_Printer();
	void TQPrint();
	void SetPrinterPropertys(UTextBlock* InTextSetterBlock, FString InTextMessage)
	{
		TextSetterBlock = InTextSetterBlock;//
		TextMessage = InTextMessage;//
	};

private:
	UTextBlock* TextSetterBlock;
	FString TextMessage;
	FString CurrentText;
	FText ConvertedText;
	int32 CharCount = 0;
	TCHAR NextChar;

	float TextPrintingDelay = 0.1f;

	FTimerHandle Delay;
	FTimerDelegate Delegate;
	FString Default = "Plz fill in the field TextMessage";
};
