// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <TQ_Utilitys/TQUtills.h>
#include <TQ_Components/Inventory/TQ_InventoryStruct.h>
#include "TQ_InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemStatStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		float Damage = 0.0f; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		float Defence = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		FInventoryItemStruct ItemInfo;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEXTQUESTGAME_API UTQ_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTQ_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	//variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Play")
		int32 slot1 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Play")
		int32 slot2 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Play")
		int32 slot3 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Play")
		int32 slot4 = 0;
	UPROPERTY(EditAnywhere, Category = "Game Play")
		TSubclassOf<UUserWidget>InventoryIsFull;

	//UPROPERTY()
	//	TArray<EItemList> ItemsInPoket;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Play")
		TArray<FItemStatStruct> Items_Display_Stats; // таблица инфы об вещи 
	UPROPERTY(BlueprintReadWrite)
		TArray <int32> ItemsIPIndexes; // множество вещей в кармане

	UPROPERTY( BlueprintReadWrite, Category = "Game Play")
		float Damage;
	UPROPERTY( BlueprintReadWrite, Category = "Game Play")
		float Defence;
	UPROPERTY(BlueprintReadWrite, Category = "Game Play")
		FString EffectToAdd;

	//events

	UFUNCTION(BlueprintCallable)
		void InventoryIsFullFunc();
	/*UFUNCTION(BlueprintCallable)
		void SetItemsInPoket(EItemList InItem, int32 Index) { ItemsInPoket[Index] = InItem; };*/
	UFUNCTION(BlueprintCallable)
		void SetIIP( int32 InItem, int32 Index) { ItemsIPIndexes[Index] = InItem; };

	UFUNCTION(BlueprintCallable)
		TArray<FItemStatStruct> GetItemsInPoketNew() { return Items_Display_Stats; };  //	new
	//UFUNCTION(BlueprintCallable)
	//	TArray<EItemList> GetItemsInPocket() { return ItemsInPoket; }
	UFUNCTION(BlueprintCallable)
		TArray</* FItemStatStruct */ int32> GetIIP() { return ItemsIPIndexes; }						//	new
	//UFUNCTION(BlueprintCallable)
	//	void SetAllItems(TArray<EItemList> Inventory) { ItemsInPoket = Inventory; };
	UFUNCTION(BlueprintCallable)
		void SaveItems(TArray<int32> Inventory) { ItemsIPIndexes = Inventory; }; //	new
	void GiveItem(int32 ItemToGive);
	void SetSlots(int32	inslot1, int32	inslot2, int32	inslot3, int32	inslot4) { slot1 = inslot1; slot2 = inslot2; slot3 = inslot3; slot4 = inslot4; };
	void RemoveItem(int32 ItemToClear);

	//float CompareItemList(EItemList Compare, bool DamagOrDefence);

	float CompareIIP(int32 Compare, bool DamagOrDefence);					//	new
	// true=Урон false=Защита
	//	void AddItemToIIP(EItemList ToIIP) {ItemsInPoket[1] = ToIIP;};


	FInventoryUpdate InventoryUpdate;
};
