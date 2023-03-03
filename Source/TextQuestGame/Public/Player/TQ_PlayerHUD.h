// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Player/TQ_PlayerHUDWidget.h"
#include <TQ_Widgets/BattleWidgets/TQ_AttackCellWidget.h>
#include "Player/TQ_PlayerHUDWidget.h"
#include "TQ_PlayerHUD.generated.h"

class UUserWidget;
class UTQ_PlayerHUDWidget;

DECLARE_MULTICAST_DELEGATE(FHUDAnsver);

DECLARE_MULTICAST_DELEGATE(FAttackCellSignatuer);
DECLARE_MULTICAST_DELEGATE_OneParam(FAttackCellDestructionSignatuer, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FAttackCellIndexSignatuer, int32);
UCLASS()// Причеши
class TEXTQUESTGAME_API ATQ_PlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "TQGame")
		TSubclassOf<UTQ_PlayerHUDWidget> TQUserInterface;
		UTQ_PlayerHUDWidget* UI;

	UFUNCTION(BlueprintCallable)
		void ReDrawTQMap(TSubclassOf<UUserWidget> Map);

	UFUNCTION(BlueprintCallable)
		void SetScreenLevelMap(TSubclassOf<UUserWidget> SetTQMap) { TQMap = SetTQMap; };

	UFUNCTION(BlueprintCallable)
		TSubclassOf<UUserWidget> GetScreenLevelMap() { return TQMap; };

		UUserWidget* GetMap() { return ItSelfMap; };

		void SkipResponce();

		void AskToPrintText();

		FString GetMessage() const { return Massage; };

		void SetMessage(FString InMessage) { Massage = InMessage; };

		void SetEHRforMessage(FText InEHRMessage) { EHRMessage = InEHRMessage; };

		void SetAttackMessage();
		void UnsetAttackMessage();

		void SetPronouncement(FText g) { Pronouncement = g; };
		void SetActionPointsScore(int32 b) { ActionPointsScore = b; };

		void FromVictory();

	FHUDAnsver HUDAncver;

	FAttackCellSignatuer ACS;
	FAttackCellDestructionSignatuer ACAS;
	FAttackCellIndexSignatuer ACIS;
private:
	UFUNCTION(BlueprintCallable)
		void ReDrawHUD();

	UPROPERTY(EditAnywhere, Category = "TQGame")
		TSubclassOf<UUserWidget> TQMap;
		UUserWidget* ItSelfMap;



		int32 ActionPointsScore;

		FText EHRMessage;

		FText Pronouncement;


		FString Massage;

};
