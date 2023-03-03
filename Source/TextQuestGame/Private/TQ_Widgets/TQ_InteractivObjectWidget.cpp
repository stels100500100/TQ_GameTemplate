// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/TQ_InteractivObjectWidget.h"
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
#include <Components/WidgetSwitcher.h>
#include <Engine/Engine.h>

#include <Player/TQ_PlayerPawn.h>
#include "TQ_Widgets/TQ_AutoCheckButton.h"
#include <TQ_Utilitys/TQUtills.h>
#include <TQ_Components/TQ_HealthComponent.h>
#include <Player/TQ_GameInstance.h>
#include <Player/TQ_PlayerHUD.h>
#include <TQ_Widgets/TQ_SpeakerWidget.h>

void UTQ_InteractivObjectWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ForbidClick(false);


	if (MainButton)
	{
		MainButton->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::UnHideIt);
	}
	if (CustomAction_1.ACh_Button)
	{
		CustomAction_1.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_1);
	}
	if (CustomAction_2.ACh_Button)
	{
		CustomAction_2.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_2);
	}
	if (CustomAction_3.ACh_Button)
	{
		CustomAction_3.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_3);
	}
	if (CustomAction_4.ACh_Button)
	{
		CustomAction_4.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_4);
	}
	if (CustomAction_5.ACh_Button)
	{
		CustomAction_5.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_5);
	}
	if (CustomAction_6.ACh_Button)
	{
		CustomAction_6.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_6);
	}
	if (CustomAction_7.ACh_Button)
	{
		CustomAction_7.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_7);
	}
	if (CustomAction_8.ACh_Button)
	{
		CustomAction_8.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_8);
	}
	if (CustomAction_9.ACh_Button)
	{
		CustomAction_9.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_9);
	}
	if (CustomAction_10.ACh_Button)
	{
		CustomAction_10.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_10);
	}
	if (CustomAction_11.ACh_Button)
	{
		CustomAction_11.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_11);
	}
	if (CustomAction_12.ACh_Button)
	{
		CustomAction_12.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_12);
	}
	if (CustomAction_13.ACh_Button)
	{
		CustomAction_13.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_13);
	}
	if (CustomAction_14.ACh_Button)
	{
		CustomAction_14.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_14);
	}
	if (CustomAction_15.ACh_Button)
	{
		CustomAction_15.ACh_Button->OnClicked.AddDynamic(this, &UTQ_InteractivObjectWidget::Custom_15);
	}
}


UTQ_GameInstance* UTQ_InteractivObjectWidget::GetGameInstance()
{
	const auto TQGameInst = Cast<UTQ_GameInstance>(GetWorld()->GetGameInstance());

	return TQGameInst;
}

void UTQ_InteractivObjectWidget::UnHideIt()
{
	Switcher->SetActiveWidgetIndex(0);
	GetWorld()->GetTimerManager().SetTimer(Delay, this, &UTQ_InteractivObjectWidget::HideIt, 10.0f, false);
}

void UTQ_InteractivObjectWidget::HideIt()
{
	pipnek = true;
	Switcher->SetActiveWidgetIndex(1);
	GetWorld()->GetTimerManager().ClearTimer(Delay);
}

void UTQ_InteractivObjectWidget::EffectHandling(FString In)
{
	if (ServiseIF)
	{
		if (!EffectCheckTable.FindKey(In))
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, TEXT("!EffectCheckTable.FindKey(In)"));
			PlayerHeandling(EEventResponseManager::Damage);
		}
	}
}

void UTQ_InteractivObjectWidget::AskToPrintText(FString In)
{
	if (ServiseIF)
	{
		MessageReprint = In;
		PlayerHeandling(EEventResponseManager::Speach);
		const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		HUD->AskToPrintText();
	}
}

void UTQ_InteractivObjectWidget::YouCanPass()
{
	ForbidClick(true);
}

void UTQ_InteractivObjectWidget::PlayerHeandling(EEventResponseManager WhatToDo)
{
	;
	const auto Character = Cast<ATQ_PlayerPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (!HUD) return;
	const auto HC = Character->FindComponentByClass<UTQ_HealthComponent>();
	if (!HC) return;
	const auto Inventory = Character->FindComponentByClass<UTQ_InventoryComponent>();
	if (!Inventory) return;

	switch (WhatToDo)
	{
	case EEventResponseManager::Damage:
		Character->TakeDamage(DamageToPlayer, FDamageEvent{}, Character->Controller, Character);
		Character->ApplayDamageToSelf(DamageToPlayer, DamageType);
		HUD->SetEHRforMessage(EHRDamageMessage);
		HUD->AskToPrintText();
		break;

	case EEventResponseManager::Speach:
		HUD->SetMessage(MessageReprint);
		HUD->SetEHRforMessage(EHRSpeachMessage);
		HUD->AskToPrintText();
		break;

	case EEventResponseManager::GoToNextMap:
		HUD->GetMap()->RemoveFromParent();
		HUD->SetScreenLevelMap(GoToMap);
		CreateWidget<UUserWidget>(this, GoToMap);
		break;

	case EEventResponseManager::Heal:
		pipnek ? HC->TryToAddHealth(HealAmount) : HC->TryToAddHunger(HealHungerAmount);
		HUD->SetMessage(MessageReprint);
		HUD->SetEHRforMessage(EHRDamageMessage);
		HUD->AskToPrintText();
		EndExistance();
		break;

	case EEventResponseManager::InventoryHandling:
		HUD->SetMessage(MessageReprint);
		HUD->SetEHRforMessage(EHRInventoryMessage);
		HUD->AskToPrintText();
		SW_EventSystems.InventiryHandlingEvents.DoUWannaToRemove ? Inventory->RemoveItem(ItemToRemove) : Inventory->GiveItem(ItemToAdd);

		EndExistance();
		break;
	default:
		break;
	}

}

void UTQ_InteractivObjectWidget::ForbidClick(bool g)
{
	if (g)
	{
		ServiseIF = true;
		/*LickButton->SetBackgroundColor(FLinearColor::White);
		PushButton->SetBackgroundColor(FLinearColor::White);
		TallkButton->SetBackgroundColor(FLinearColor::White);
		FlirtButton->SetBackgroundColor(FLinearColor::White);
		DrinkButton->SetBackgroundColor(FLinearColor::White);
		EatButton->SetBackgroundColor(FLinearColor::White);
		BiteButton->SetBackgroundColor(FLinearColor::White);
		KissButton->SetBackgroundColor(FLinearColor::White);
		TakeButton->SetBackgroundColor(FLinearColor::White);*/
	}
	else
	{
		ServiseIF = false;
		/*LickButton->SetBackgroundColor(FLinearColor::Black);
		PushButton->SetBackgroundColor(FLinearColor::Black);
		TallkButton->SetBackgroundColor(FLinearColor::Black);
		FlirtButton->SetBackgroundColor(FLinearColor::Black);
		DrinkButton->SetBackgroundColor(FLinearColor::Black);
		EatButton->SetBackgroundColor(FLinearColor::Black);
		BiteButton->SetBackgroundColor(FLinearColor::Black);
		TakeButton->SetBackgroundColor(FLinearColor::Black);
		KissButton->SetBackgroundColor(FLinearColor::Black);*/
	}
}

void UTQ_InteractivObjectWidget::EndExistance()
{
	SetVisibility(ESlateVisibility::Collapsed);

	GetGameInstance()->MapState[CreatorsName].IsHiddenObjectExist = false;
	GetGameInstance()->MapState[CreatorsName].IsObsticleVisible = false;
	
	OnDestroyItem.Broadcast();

}

void UTQ_InteractivObjectWidget::BaseInteractionEvent(bool FinalResault, bool IsDestroyOn, TSubclassOf<UUserWidget>& a, EEventResponseManager& b, FName ActionName)
{
	if (FinalResault)
	{
		GoToMap = a;

		SW_EventSystems.NarrationEvent.TextMessage = MessageReprint;
		if (IsDestroyOn)
		{
			EndExistance();
		}
		if (ActionName == "Drink")
		{
			pipnek = false;
			HealHungerAmount = HealHungerAmount / 2.0f;
			PlayerHeandling(EEventResponseManager::Heal);
		}
		if (ActionName == "Eat")
		{
			pipnek = false;
			PlayerHeandling(EEventResponseManager::Heal);
			pipnek = true;
		}
		else
		{
			PlayerHeandling(b);
		}


	}
	else
	{
		PlayerHeandling(EEventResponseManager::Damage);
	}
}

void UTQ_InteractivObjectWidget::Custom_1()
{
	 ItemToRemove = CustomAction_1.ItemToRemove;
	 ItemToAdd = CustomAction_1.ItemToAdd;

	BaseInteractionEvent(CustomAction_1.ACh_Button->FinalResault,		//
		CustomAction_1.DestroyOn_BInfo_, CustomAction_1.GoTo_BInfo_Map, //
		CustomAction_1.BInfo_Event, CustomAction_1.ActionName);			//
}

void UTQ_InteractivObjectWidget::Custom_2()
{
	ItemToRemove = CustomAction_2.ItemToRemove;
	ItemToAdd = CustomAction_2.ItemToAdd;

	BaseInteractionEvent(CustomAction_2.ACh_Button->FinalResault,		//
		CustomAction_2.DestroyOn_BInfo_, CustomAction_2.GoTo_BInfo_Map, //
		CustomAction_2.BInfo_Event, CustomAction_2.ActionName);			//
}

void UTQ_InteractivObjectWidget::Custom_3()
{
	ItemToRemove = CustomAction_3.ItemToRemove;
	ItemToAdd = CustomAction_3.ItemToAdd;

	BaseInteractionEvent(CustomAction_3.ACh_Button->FinalResault,		//
		CustomAction_3.DestroyOn_BInfo_, CustomAction_3.GoTo_BInfo_Map, //
		CustomAction_3.BInfo_Event, CustomAction_3.ActionName);			//
}

void UTQ_InteractivObjectWidget::Custom_4()
{
	ItemToRemove = CustomAction_4.ItemToRemove;
	ItemToAdd = CustomAction_4.ItemToAdd;

	BaseInteractionEvent(CustomAction_4.ACh_Button->FinalResault,		//
		CustomAction_4.DestroyOn_BInfo_, CustomAction_4.GoTo_BInfo_Map, //
		CustomAction_4.BInfo_Event, CustomAction_4.ActionName);			//
}

void UTQ_InteractivObjectWidget::Custom_5()
{
	ItemToRemove = CustomAction_5.ItemToRemove;
	ItemToAdd = CustomAction_5.ItemToAdd;

	BaseInteractionEvent(CustomAction_5.ACh_Button->FinalResault,		//
		CustomAction_5.DestroyOn_BInfo_, CustomAction_5.GoTo_BInfo_Map, //
		CustomAction_5.BInfo_Event, CustomAction_5.ActionName);			//
}

void UTQ_InteractivObjectWidget::Custom_6()
{
	ItemToRemove = CustomAction_6.ItemToRemove;
	ItemToAdd = CustomAction_6.ItemToAdd;

	BaseInteractionEvent(CustomAction_6.ACh_Button->FinalResault,		//
		CustomAction_6.DestroyOn_BInfo_, CustomAction_6.GoTo_BInfo_Map, //
		CustomAction_6.BInfo_Event, CustomAction_6.ActionName);			//
}
void UTQ_InteractivObjectWidget::Custom_7()
{
	ItemToRemove = CustomAction_7.ItemToRemove;
	ItemToAdd = CustomAction_7.ItemToAdd;

	BaseInteractionEvent(CustomAction_7.ACh_Button->FinalResault,		//
		CustomAction_7.DestroyOn_BInfo_, CustomAction_7.GoTo_BInfo_Map, //
		CustomAction_7.BInfo_Event, CustomAction_7.ActionName);			//
}
void UTQ_InteractivObjectWidget::Custom_8()
{
	ItemToRemove = CustomAction_8.ItemToRemove;
	ItemToAdd = CustomAction_8.ItemToAdd;

	BaseInteractionEvent(CustomAction_8.ACh_Button->FinalResault,		//
		CustomAction_8.DestroyOn_BInfo_, CustomAction_8.GoTo_BInfo_Map, //
		CustomAction_8.BInfo_Event, CustomAction_8.ActionName);			//
}
void UTQ_InteractivObjectWidget::Custom_9()
{
	ItemToRemove = CustomAction_9.ItemToRemove;
	ItemToAdd = CustomAction_9.ItemToAdd;

	BaseInteractionEvent(CustomAction_9.ACh_Button->FinalResault,		//
		CustomAction_9.DestroyOn_BInfo_, CustomAction_9.GoTo_BInfo_Map, //
		CustomAction_9.BInfo_Event, CustomAction_9.ActionName);			//
}

void UTQ_InteractivObjectWidget::Custom_10()
{
	ItemToRemove = CustomAction_10.ItemToRemove;
	ItemToAdd = CustomAction_10.ItemToAdd;

	BaseInteractionEvent(CustomAction_10.ACh_Button->FinalResault,			//
		CustomAction_10.DestroyOn_BInfo_, CustomAction_10.GoTo_BInfo_Map,	//
		CustomAction_10.BInfo_Event, CustomAction_10.ActionName);			//
}
void UTQ_InteractivObjectWidget::Custom_11()
{
	ItemToRemove = CustomAction_11.ItemToRemove;
	ItemToAdd = CustomAction_11.ItemToAdd;

	BaseInteractionEvent(CustomAction_11.ACh_Button->FinalResault,			//
		CustomAction_11.DestroyOn_BInfo_, CustomAction_11.GoTo_BInfo_Map,	//
		CustomAction_11.BInfo_Event, CustomAction_11.ActionName);			//
}
void UTQ_InteractivObjectWidget::Custom_12()
{
	ItemToRemove = CustomAction_12.ItemToRemove;
	ItemToAdd = CustomAction_12.ItemToAdd;

	BaseInteractionEvent(CustomAction_12.ACh_Button->FinalResault,			//
		CustomAction_12.DestroyOn_BInfo_, CustomAction_12.GoTo_BInfo_Map,   //
		CustomAction_12.BInfo_Event, CustomAction_12.ActionName);			//
}
void UTQ_InteractivObjectWidget::Custom_13()
{
	ItemToRemove = CustomAction_13.ItemToRemove;
	ItemToAdd = CustomAction_13.ItemToAdd;

	BaseInteractionEvent(CustomAction_13.ACh_Button->FinalResault,			//
		CustomAction_13.DestroyOn_BInfo_, CustomAction_13.GoTo_BInfo_Map,	//
		CustomAction_13.BInfo_Event, CustomAction_13.ActionName);			//
}
void UTQ_InteractivObjectWidget::Custom_14()
{
	ItemToRemove = CustomAction_14.ItemToRemove;
	ItemToAdd = CustomAction_14.ItemToAdd;

	BaseInteractionEvent(CustomAction_14.ACh_Button->FinalResault,			//
		CustomAction_14.DestroyOn_BInfo_, CustomAction_14.GoTo_BInfo_Map,	//
		CustomAction_14.BInfo_Event, CustomAction_14.ActionName);			//
}
void UTQ_InteractivObjectWidget::Custom_15()
{
	ItemToRemove = CustomAction_15.ItemToRemove;
	ItemToAdd = CustomAction_15.ItemToAdd;

	BaseInteractionEvent(CustomAction_15.ACh_Button->FinalResault,			//
		CustomAction_15.DestroyOn_BInfo_, CustomAction_15.GoTo_BInfo_Map,	//
		CustomAction_15.BInfo_Event, CustomAction_15.ActionName);			//
}