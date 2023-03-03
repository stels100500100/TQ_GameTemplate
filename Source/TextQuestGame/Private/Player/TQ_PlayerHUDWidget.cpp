// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TQ_PlayerHUDWidget.h"

#include <Engine/Engine.h>
#include <Kismet\GameplayStatics.h>
#include "Components/ProgressBar.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include <Player/TQ_PlayerHUD.h>
#include <Player/TQ_PlayerPawn.h>
#include <TQ_Utilitys/TQUtills.h>
#include <TQ_Components/TQ_InventoryComponent.h>
#include <TQ_Components/TQ_HealthComponent.h>
#include <TQ_Components/Inventory/TQ_InventoryCell.h>
#include <TQ_Widgets/BattleWidgets/TQ_AttackCellWidget.h>
#include <TQ_Widgets/TQ_SpeakerWidget.h>
#include <TQ_Widgets/TQ_BaseLevelWidget.h>

DEFINE_LOG_CATEGORY_STATIC(PHUDW,All,All)

void UTQ_PlayerHUDWidget::NativeOnInitialized()
{

	GetInventoriComp()->InventoryUpdate.AddUObject(this, &UTQ_PlayerHUDWidget::DrawInventory);
	if (OpenEffectsPannel)
	{
		OpenEffectsPannel->OnClicked.AddDynamic(this, &UTQ_PlayerHUDWidget::DrawEffectTable);
	}
	if (OpenMenuPannel)
	{
		OpenMenuPannel->OnClicked.AddDynamic(this, &UTQ_PlayerHUDWidget::DrawMenuTable);
	}
	if (EffectsPannel)
	{

	}
	DrawInventory();

}

ATQ_PlayerPawn* UTQ_PlayerHUDWidget::CastToTQPlayer() const
{
	const auto Player = Cast<ATQ_PlayerPawn>(GetOwningPlayerPawn());
	return Player;
}

UTQ_InventoryComponent* UTQ_PlayerHUDWidget::GetInventoriComp() const
{
	const auto Component = CastToTQPlayer()->GetComponentByClass(UTQ_InventoryComponent::StaticClass());
	const auto InventoryComponent = Cast<UTQ_InventoryComponent>(Component);
	return InventoryComponent;
}

void UTQ_PlayerHUDWidget::MRGminus()
{
	Mrgn = Mrgn + FMargin(-50.0f, -25.0f);
}

float UTQ_PlayerHUDWidget::GetHealthPercent() const
{
	const auto Component = CastToTQPlayer()->GetComponentByClass(UTQ_HealthComponent::StaticClass());

	const auto HealthComponent = Cast<UTQ_HealthComponent>(Component);

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

float UTQ_PlayerHUDWidget::GetHungerPercent() const
{
	const auto Component = CastToTQPlayer()->GetComponentByClass(UTQ_HealthComponent::StaticClass());

	const auto HealthComponent = Cast<UTQ_HealthComponent>(Component);

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHungerPercent();
}

void UTQ_PlayerHUDWidget::DrawInventory()
{
	InventoryVBox->ClearChildren();
	UE_LOG(PHUDW,Display,TEXT("DrawInventory"))
	if (!GetWorld() || !InventoryVBox) return;

	if (GetInventoriComp()->slot1 != 0)
	{
		if (!SlotUsed1)
		{
			InventoryCellWidget = CreateWidget<UTQ_InventoryCell>(GetWorld(), Slot1);
			InventoryCellWidget->SetItem(GetInventoriComp()->slot1);
			//GetInventoriComp()->SetItemsInPoket(InventoryCellWidget->Item[GetInventoriComp()->slot1].Item, 0); // не нужно Наверное..
			//CastToTQPlayer()->AddEffect(InventoryCellWidget->Item[GetInventoriComp()->slot1].Effect);// не нужно
			CastToTQPlayer()->AddEffect(GetInventoriComp()->GetItemsInPoketNew()[GetInventoriComp()->slot1].ItemInfo.Effect); // новый
			InventoryVBox->AddChild(InventoryCellWidget);
			SlotUsed1 = true;
		}

	}

	if (GetInventoriComp()->slot2 != 0)
	{
		if (!SlotUsed2)
		{
			InventoryCellWidget = CreateWidget<UTQ_InventoryCell>(GetWorld(), Slot2);
			InventoryCellWidget->SetItem(GetInventoriComp()->slot2);
		//	GetInventoriComp()->SetItemsInPoket(InventoryCellWidget->Item[GetInventoriComp()->slot2].Item, 1);
			//CastToTQPlayer()->AddEffect(InventoryCellWidget->Item[GetInventoriComp()->slot2].Effect);
			CastToTQPlayer()->AddEffect(GetInventoriComp()->GetItemsInPoketNew()[GetInventoriComp()->slot1].ItemInfo.Effect);
			InventoryVBox->AddChild(InventoryCellWidget);
			SlotUsed2 = true;
		}
	}

	if (GetInventoriComp()->slot3 != 0)
	{
		if (!SlotUsed3)
		{
			InventoryCellWidget = CreateWidget<UTQ_InventoryCell>(GetWorld(), Slot3);
			InventoryCellWidget->SetItem(GetInventoriComp()->slot3);
			//GetInventoriComp()->SetItemsInPoket(InventoryCellWidget->Item[GetInventoriComp()->slot3].Item, 2);
			//CastToTQPlayer()->AddEffect(InventoryCellWidget->Item[GetInventoriComp()->slot3].Effect);
			CastToTQPlayer()->AddEffect(GetInventoriComp()->GetItemsInPoketNew()[GetInventoriComp()->slot1].ItemInfo.Effect);
			InventoryVBox->AddChild(InventoryCellWidget);
			SlotUsed3 = true;
		}
	}

	if (GetInventoriComp()->slot4 != 0)
	{
		if (!SlotUsed4)
		{
			InventoryCellWidget = CreateWidget<UTQ_InventoryCell>(GetWorld(), Slot4);
			InventoryCellWidget->SetItem(GetInventoriComp()->slot4);
			//GetInventoriComp()->SetItemsInPoket(InventoryCellWidget->Item[GetInventoriComp()->slot4].Item, 3);
			//CastToTQPlayer()->AddEffect(InventoryCellWidget->Item[GetInventoriComp()->slot4].Effect);
			CastToTQPlayer()->AddEffect(GetInventoriComp()->GetItemsInPoketNew()[GetInventoriComp()->slot1].ItemInfo.Effect);
			InventoryVBox->AddChild(InventoryCellWidget);
			SlotUsed4 = true;
		}
		else
		{
			GetInventoriComp()->InventoryIsFullFunc();
		}

	}
}

void UTQ_PlayerHUDWidget::DrawMessage()
{
	SpeakerWidget = CreateWidget<UTQ_SpeakerWidget>(GetWorld(), TSOSpeakerWidget);

	SpeakerWidget->PrintEffectDisc(EHRTransfer);

	SpeakerWidget->AddToViewport(2);
	SpeakerWidget->SetPadding(Mrgn);
	MessageBoxOverlay->AddChild(SpeakerWidget);
	Mrgn = Mrgn + FMargin(+50.0f, +25.0f);

}

void UTQ_PlayerHUDWidget::DrawEffectTable()
{
	PlayAnimationForward(OpenEffectsPannelAnimation);


	for (int32 A = 0; A <= CastToTQPlayer()->Effects.Num() - 1; A++)
	{
		PreConcotinateVar = CastToTQPlayer()->Effects[A];
		ConcotinateVar = ConcotinateVar + PreConcotinateVar + " ";
		Cad = Cad.FromString(ConcotinateVar);
		EffectsPannel->SetText(Cad);
	}
	GetWorld()->GetTimerManager().SetTimer(HideEffectTable, this, &UTQ_PlayerHUDWidget::UnDrawEffectTable, 5.f, false);
}
void UTQ_PlayerHUDWidget::DrawMenuTable()
{
	PlayAnimationForward(OpenMemuPannelAnimation);
	GetWorld()->GetTimerManager().SetTimer(HideMenuTable, this, &UTQ_PlayerHUDWidget::UnDrawMenuTable, 5.f, false);

}


void UTQ_PlayerHUDWidget::UnDrawEffectTable()
{
	PlayAnimationReverse(OpenEffectsPannelAnimation);
	ConcotinateVar = "";
	Cad = Cad.FromString(ConcotinateVar);
}

void UTQ_PlayerHUDWidget::UnDrawMenuTable()
{
	PlayAnimationReverse(OpenMemuPannelAnimation);
}

void UTQ_PlayerHUDWidget::MakeACW(int32 f, FText b) 
{
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	ACWidget = CreateWidget<UTQ_AttackCellWidget>(GetWorld(), AttackCellWidget);
	ACWidget->SetBattleStats(f, b);
	ACWidget->SetBattleStatsVisually();
	ACWidget->AddToViewport(2);
	MessageBox->AddChild(ACWidget);
	HUD->ACIS.Broadcast(ACWCounter);
	ACWCounter++;
	ACWCounterForDeletion = ACWCounter;
}

void UTQ_PlayerHUDWidget::UNMakeACW() 
{
		const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

		if (ReversedCounterDeletion <= ACWCounter)
		{
			HUD->ACAS.Broadcast(ReversedCounterDeletion);
			ReversedCounterDeletion++;

		}
}

void UTQ_PlayerHUDWidget::DestroyAllContent()
{
	while (ACWCounterForDeletion != 0)
	{
			MessageBox->RemoveChildAt(ACWCounterForDeletion);
		ACWCounterForDeletion--;
	}
	ReversedCounterDeletion = 1;
	ACWCounterForDeletion = 1;
	ACWCounter = 1;
}