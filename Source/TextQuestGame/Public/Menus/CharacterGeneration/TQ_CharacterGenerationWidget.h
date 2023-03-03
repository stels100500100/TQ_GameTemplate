// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TQ_CharacterGenerationWidget.generated.h"

class UWidgetAnimation;
class UButton;
class UTextBlock;
class UTQ_Printer;

UCLASS() 
class TEXTQUESTGAME_API UTQ_CharacterGenerationWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	//Buttons

	UPROPERTY(meta = (BindWidget))
		UButton* ReadyButton;
	UPROPERTY(meta = (BindWidget))
		UButton* LuckPPButton;
	UPROPERTY(meta = (BindWidget))
		UButton* LuckMMButton;
	UPROPERTY(meta = (BindWidget))
		UButton* StrengthPPButton;
	UPROPERTY(meta = (BindWidget))
		UButton* StrengthMMButton;
	UPROPERTY(meta = (BindWidget))
		UButton* IntellegencePPButton;
	UPROPERTY(meta = (BindWidget))
		UButton* IntellegenceMMButton;


	UPROPERTY(meta = (BindWidget))
		UTextBlock* ExperienceScore;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextSetterBlock;


	//MetricVar-s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		int32 CriticalLuckChanse = 3;
	UPROPERTY( BlueprintReadWrite, Category = "TQGame")
		int32 Luck = 0;
	UPROPERTY( BlueprintReadWrite, Category = "TQGame")
		int32 Strength = 0;
	UPROPERTY( BlueprintReadWrite, Category = "TQGame")
		int32 Intellegentce = 0;
		int32 CriticalLuckTestLimiter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		int32 ExpiriancePoints = 10;


	UPROPERTY(EditAnywhere, Category = "TQGame")
		float TextPrintingDelay = 0.1f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FName NormalRootLevel = "DefaultLevel";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FName LukyRootLevel = "DefaultLevel";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FName ExtraLukyRootLevel = "DefaultLevel";


	UPROPERTY(EditAnywhere, Category = "TQGame")
		FString TextMessage;


		//Animations
	UPROPERTY(meta = (BindWidgetAnim), Transient, meta = (ToolTip = "Animation that showup on critical luck"))
		UWidgetAnimation* CriticalLuckAnimation;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UUserWidget> FirstCriticalFailScreenClass;
		UUserWidget* FirstCriticalFailScreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UUserWidget> SecondCriticalFailScreenClass;
		UUserWidget* SecondCriticalFailScreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UUserWidget> ThirdCriticalFailScreenClass;
		UUserWidget* ThirdCriticalFailScreenWidget;


		FTimerHandle Delay;
private:

		virtual void NativeOnInitialized() override;

		void PrintTextMessage();

	UFUNCTION()
		void CriticalLuck();
	UFUNCTION()
		void CriticalFailure();
	UFUNCTION()
		bool RandomGenirator();
	UFUNCTION()
		void Ready();

	UFUNCTION()
		void LuckMinus() { if (Luck > 0) { Luck = Luck--; ExpiriancePoints++; } };
	UFUNCTION()
		void LuckPlus() { if (ExpiriancePoints > 0) { Luck = Luck++; ExpiriancePoints--; } };
	UFUNCTION()
		void StrengthMinus() { if (Strength > 0) { Strength = Strength--; ExpiriancePoints++; } };
	UFUNCTION()
		void StrengthPlus() { if (ExpiriancePoints > 0) { Strength = Strength++; ExpiriancePoints--; } };
	UFUNCTION()
		void IntelegentceMinus() { if (Intellegentce > 0) { Intellegentce = Intellegentce--; ExpiriancePoints++; } };
	UFUNCTION()
		void IntellegentcePlus() { if (ExpiriancePoints > 0) { Intellegentce = Intellegentce++; ExpiriancePoints--; } };
	UFUNCTION(BlueprintType)
		int32 GetScore() { return ExpiriancePoints; };
};
