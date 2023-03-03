// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TQ_InventoryCell.generated.h"

class UButton;
class UTexture2D;
class UTextBlock;
class UImage;

UCLASS()
class TEXTQUESTGAME_API UTQ_InventoryCell : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void SetItem(int32 SetItem);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FInventoryItemStruct> Item;

private:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
		void UnhideDiscription();
	UFUNCTION(BlueprintCallable)
		void HideDiscription();
	UFUNCTION()
		UTQ_InventoryComponent* GetInventory();
	UFUNCTION(BlueprintCallable)
		void RemoveItSelf();


	UPROPERTY(meta = (BindWidget), EditAnywhere)
		UButton* SlotButton;

	UPROPERTY(meta = (BindWidget), EditAnywhere)
		UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget), EditAnywhere)
		UButton* RemoveButton;

	UPROPERTY(meta = (BindWidget), EditAnywhere)
		UTextBlock* Description;

	UPROPERTY(EditAnywhere)
		UTexture2D* DefaultIcon;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* ShowAnimation;


		int32 ItemInICell;

		FTimerHandle Timer;

};
