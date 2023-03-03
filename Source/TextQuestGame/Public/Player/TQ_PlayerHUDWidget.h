// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TQ_Widgets/BattleWidgets/TQ_AttackCellWidget.h"
#include "TQ_Components/TQ_InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include <Player/TQ_PlayerPawn.h>
#include "TQ_PlayerHUDWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UVerticalBox;
class UOverlay;
class UHorizontalBox;
class UButton;
class UWidgetAnimation;
class ATQ_PlayerPawn;
class UTQ_SpeakerWidget;
class UTQ_InventoryCell;
class UTQ_AttackCellWidget;

UCLASS()
class TEXTQUESTGAME_API UTQ_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
		void MRGminus();

	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable)
		float GetHungerPercent() const;

	UFUNCTION(BlueprintCallable)
		void DrawInventory();
	UFUNCTION(BlueprintCallable)
		void DrawMessage();
	UFUNCTION(BlueprintCallable)
		void SetEHRTransfer(FText InEHR) { EHRTransfer = InEHR; };
	UFUNCTION(BlueprintCallable)
		void MakeACW(int32 f, FText b);
	UFUNCTION(BlueprintCallable)
		void UNMakeACW();
	UFUNCTION(BlueprintCallable)
		void DestroyAllContent();

protected:
	virtual void NativeOnInitialized() override;

	ATQ_PlayerPawn* CastToTQPlayer() const;
	UTQ_InventoryComponent* GetInventoriComp() const;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UTQ_InventoryCell> Slot1;
	bool SlotUsed1 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UTQ_InventoryCell> Slot2;
	bool SlotUsed2 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UTQ_InventoryCell> Slot3;
	bool SlotUsed3 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UTQ_InventoryCell> Slot4;
	bool SlotUsed4 = false;
		UTQ_InventoryCell* InventoryCellWidget;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UTQ_SpeakerWidget> TSOSpeakerWidget;
		UTQ_SpeakerWidget* SpeakerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UTQ_AttackCellWidget> AttackCellWidget;
		UTQ_AttackCellWidget* ACWidget;

private:
	UFUNCTION()
		void DrawEffectTable();
	UFUNCTION()
		void DrawMenuTable();
	UFUNCTION()
		void UnDrawEffectTable();
	UFUNCTION()
		void UnDrawMenuTable();

	UPROPERTY(meta = (BindWidget))
		UVerticalBox* InventoryVBox;
	UPROPERTY(meta = (BindWidget))
		UHorizontalBox* MessageBox;
	UPROPERTY(meta = (BindWidget))
		UOverlay* MessageBoxOverlay;

	UPROPERTY(meta = (BindWidget), EditAnywhere)
		UProgressBar* Pbar;

	UPROPERTY(meta = (BindWidget), EditAnywhere)
		UProgressBar* HungerBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* EffectsPannel;
	UPROPERTY(meta = (BindWidget))
		UButton* OpenEffectsPannel;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* OpenEffectsPannelAnimation;

	UPROPERTY(meta = (BindWidget))
		UButton* OpenMenuPannel;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* OpenMemuPannelAnimation;


		int32 ACWCounter = 1;
		int32 ACWCounterForDeletion = 1;
		int32 ReversedCounterDeletion = 1;


		FString Message;
		FMargin Mrgn = FMargin(0.0f, 0.0f);
		FText EHRTransfer;
		FTimerHandle HideEffectTable;
		FTimerHandle HideMenuTable;


		FString ConcotinateVar = "";
		FString PreConcotinateVar = "";
		FText Cad;
};
