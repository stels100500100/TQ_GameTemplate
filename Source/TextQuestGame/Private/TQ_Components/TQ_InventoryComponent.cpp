// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Components/TQ_InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include <TQ_Components/Inventory/TQ_InventoryStruct.h>

UTQ_InventoryComponent::UTQ_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTQ_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	ItemsIPIndexes={ slot1, slot2, slot3, slot4 };
}


void UTQ_InventoryComponent::GiveItem(int32 ItemToGive)
{
		if (slot1 == 0)
		{
			slot1 = ItemToGive;
			ItemsIPIndexes[0] = ItemToGive;
		}
		else
			if (slot2 == 0)
			{
				slot2 = ItemToGive;
				ItemsIPIndexes[1] = ItemToGive;

			}
			else
				if (slot3 == 0)
				{
					slot3 = ItemToGive;
					ItemsIPIndexes[2] = ItemToGive;

				}
				else
					if (slot4 == 0)
					{
						slot4 = ItemToGive;
						ItemsIPIndexes[3] = ItemToGive;

					}
	InventoryUpdate.Broadcast();
}

void UTQ_InventoryComponent::RemoveItem(int32 ItemToClear)
{
	if (slot1 == ItemToClear)
	{
		slot1 = 0;
		ItemsIPIndexes[0] = 0;

	}
	else if (slot2 == ItemToClear)
	{
		slot2 = 0;
		ItemsIPIndexes[1] = 0;

	}
	else if (slot3 == ItemToClear)
	{
		slot3 = 0;
		ItemsIPIndexes[2] = 0;

	}
	else if (slot4 == ItemToClear)
	{
		slot4 = 0;
		ItemsIPIndexes[3] = 0;

	}
	InventoryUpdate.Broadcast();
}



void UTQ_InventoryComponent::InventoryIsFullFunc()
{
	CreateWidget<UUserWidget>(GetWorld(), InventoryIsFull)->AddToViewport(2);
}


float UTQ_InventoryComponent::CompareIIP(int32 Compare, bool DamagOrDefence)
{
	float Resoult = 0.0f;
	Damage += Items_Display_Stats[Compare].Damage;
	Defence += Items_Display_Stats[Compare].Defence ;
	Resoult = DamagOrDefence ? Damage : Defence;

	return Resoult;
}
