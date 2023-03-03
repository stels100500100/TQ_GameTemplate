// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <TQ_Utilitys/TQUtills.h>
#include "Blueprint/UserWidget.h"

#include "TQ_SpeakerWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()// причеши 
class TEXTQUESTGAME_API UTQ_SpeakerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void PrintEffectDisc(FText InEffectHDiscription);
	FSpeakerRequest SReq;

private:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
		void MakeRequest();

	UFUNCTION()
		void Skip();
		void PrintTextMessage();

	UPROPERTY(meta = (BindWidget))
		UButton* SkipButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextSetterBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* EffectHDiscriptionBlock;

	UPROPERTY(EditAnywhere, Category = "TQGame")
		float TextPrintingDelay = 0.1f;

	UPROPERTY(EditAnywhere, Category = "TQGame")
		FString TextMessage;
		FString CurrentText;

		FText ConvertedText;
		int32 CharCount = 0;
		TCHAR NextChar;

		FTimerHandle Delay;
};
