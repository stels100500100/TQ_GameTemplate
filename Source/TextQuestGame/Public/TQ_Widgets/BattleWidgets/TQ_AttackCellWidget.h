// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TQ_AttackCellWidget.generated.h"

class UTextBlock;
class UButton;
class UWidgetAnimation;

UCLASS()
class TEXTQUESTGAME_API UTQ_AttackCellWidget : public UUserWidget
{
	GENERATED_BODY()

private:
		virtual void NativeOnInitialized() override;
	bool Seted = true;
	int32 BaseDeleteIndex;
	int32 Score;
	FText ActionName;
	UPROPERTY(meta = (BindWidget))
		UButton* Cancel;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ScoreTB; 
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ActionNameTB;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBX; 

	FTimerHandle DeleteHandle;

public:
	UFUNCTION(BlueprintCallable)
		void SetBaseDeleteIndex(int32 DeleteIndexSetter);
	UFUNCTION(BlueprintCallable)
		void SetBattleCellScore(int32 In) { Score = In; };
	UFUNCTION(BlueprintCallable)
		void SetActionName(FText In) { ActionName = In; };
	UFUNCTION(BlueprintCallable)
		void SetBattleStats(int32 In, FText TIn) { Score = In; ActionName = TIn; };
	UFUNCTION(BlueprintCallable)
		void DestroyBattleCell(); //rename
	UFUNCTION(BlueprintCallable)
		void SetBattleStatsVisually(); //rename
	UFUNCTION(BlueprintCallable)
		void EndAnimation(int32 DeleteIndex);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* OnDestroy;

};
