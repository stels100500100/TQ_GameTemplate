// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include <TQ_Utilitys/TQUtills.h>
#include "TQ_AutoCheckButton.generated.h"


UCLASS()
class TEXTQUESTGAME_API UTQ_AutoCheckButton : public UButton
{
	GENERATED_BODY()
public:

		UTQ_AutoCheckButton(const FObjectInitializer& ObjectInit);

		void SetAllStats(EStatusAutoCheck& InSelectionVar, int32& Requirment, FString& OnSuccess, FString& OnFail, FString& CheckedEffect, FString& InDescription)
		{

			SelectionVar = InSelectionVar;
			StatPihvaRequirement = Requirment;
			MessageOnSuccess = OnSuccess;
			MessageOnFail = OnFail;
			EffectToCheck = CheckedEffect;
			EffectDescription = InDescription;

		};

		bool FinalResault = true;
	FCheckStatusAutoSignature OnStatusAutoChecked;
	FCheckEffectAutoSignature OnEffectAutoChecked;

private:
	UFUNCTION(BlueprintCallable)
		bool CheckStats(EStatusAutoCheck WhatToCheck);
	UFUNCTION(BlueprintCallable)
		void GiveResoult();


	UPROPERTY(EditAnywhere, Category = "TQGame")
		EStatusAutoCheck SelectionVar = EStatusAutoCheck::Luck;

	UPROPERTY(EditAnywhere,  Category = "TQGame", meta = (ClampMin = "0", ClampMax = "10"))
		int32 StatPihvaRequirement;

	UPROPERTY(EditAnywhere,  Category = "TQGame")
		FString MessageOnSuccess;

	UPROPERTY(EditAnywhere,  Category = "TQGame")
		FString MessageOnFail;

	UPROPERTY(EditAnywhere,  Category = "TQGame")
		FString EffectToCheck = "DefaultEffectToCheck";

	UPROPERTY(EditAnywhere,  Category = "TQGame")
		FString EffectDescription = "DefaultEffectDescription";
};
