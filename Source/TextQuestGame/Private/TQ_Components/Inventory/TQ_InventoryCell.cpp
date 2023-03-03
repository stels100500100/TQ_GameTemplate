// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Components/Inventory/TQ_InventoryCell.h"


#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include <Blueprint/UserWidget.h>

#include <Player/TQ_PlayerPawn.h>
#include "TQ_Components/TQ_InventoryComponent.h"
#include <TQ_Components/Inventory/TQ_InventoryStruct.h>
DEFINE_LOG_CATEGORY_STATIC(InventoryCellLog, All, All)

void UTQ_InventoryCell::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Description)
	{
		Description->SetAutoWrapText(true);
		Description->SetVisibility(ESlateVisibility::Hidden);
	}
	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UTQ_InventoryCell::UnhideDiscription);
	}
	if (RemoveButton)
	{
		RemoveButton->OnClicked.AddDynamic(this, &UTQ_InventoryCell::RemoveItSelf);
	}
	if (ItemIcon)
	{
		ItemIcon->SetBrushFromTexture(DefaultIcon);
	}
}

UTQ_InventoryComponent* UTQ_InventoryCell::GetInventory()
{
	const auto Char = Cast<ATQ_PlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	const auto Inventory = Char->FindComponentByClass<UTQ_InventoryComponent>();
	return Inventory;
}

void UTQ_InventoryCell::SetItem(int32 SetItem)
{
		ItemInICell = SetItem;
		ItemIcon->SetBrushFromTexture(GetInventory()->GetItemsInPoketNew()[SetItem].ItemInfo.Icon);
		//ItemIcon->SetBrushFromTexture(Item[SetItem].Icon);
		Description->SetText(GetInventory()->GetItemsInPoketNew()[SetItem].ItemInfo.Discription);
		//Description->SetText(Item[SetItem].Discription);
		
}


void UTQ_InventoryCell::UnhideDiscription()
{
	PlayAnimation(ShowAnimation);
	Description->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UTQ_InventoryCell::HideDiscription, 10.0f);
}


void UTQ_InventoryCell::HideDiscription()
{
	PlayAnimationReverse(ShowAnimation);
	Description->SetVisibility(ESlateVisibility::Hidden);
}

void UTQ_InventoryCell::RemoveItSelf()
{
	GetInventory()->RemoveItem(ItemInICell);
	RemoveFromParent();
}