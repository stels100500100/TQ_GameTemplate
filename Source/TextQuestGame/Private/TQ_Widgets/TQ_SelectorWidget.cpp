// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/TQ_SelectorWidget.h"

#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
#include <Components/WidgetSwitcher.h>

#include <Player/TQ_PlayerPawn.h>
#include "TQ_Widgets/TQ_AutoCheckButton.h"
#include <TQ_Utilitys/TQUtills.h>
#include <TQ_Components/TQ_HealthComponent.h>
#include <Player/TQ_GameInstance.h>
#include <Player/TQ_PlayerHUD.h>
#include <TQ_Widgets/TQ_SpeakerWidget.h>


void UTQ_SelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ForbidClick(false);


	if (MainButton)
	{
		MainButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::UnHideIt);
	}
	if (LickButton)
	{
		LickButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::Lick);
		LickButton->OnEffectAutoChecked.AddUObject(this, &UTQ_SelectorWidget::EffectHandling);
		LickButton->OnStatusAutoChecked.AddUObject(this, &UTQ_SelectorWidget::AskToPrintText);
		LickButton->SetAllStats(LickToCheck, LickStatRequirement, LickMessageOnSuccess,	//..
			LickMessageOnFail, LickEffectToCheck, LickEffectDescription);
		HideIt();
	}
	if (PushButton)
	{
		PushButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::Push);
		PushButton->OnEffectAutoChecked.AddUObject(this, &UTQ_SelectorWidget::EffectHandling);
		PushButton->OnStatusAutoChecked.AddUObject(this, &UTQ_SelectorWidget::AskToPrintText);
		PushButton->SetAllStats(PushToCheck, PushStatRequirement, PushMessageOnSuccess,	//..
			PushMessageOnFail, PushEffectToCheck, PushEffectDescription);
		HideIt();
	}
	if (TallkButton)
	{
		TallkButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::Tallk);
		TallkButton->OnEffectAutoChecked.AddUObject(this, &UTQ_SelectorWidget::EffectHandling);
		TallkButton->OnStatusAutoChecked.AddUObject(this, &UTQ_SelectorWidget::AskToPrintText);
		TallkButton->SetAllStats(TallkToCheck, TallkStatRequirement, TallkMessageOnSuccess,	//..
			TallkMessageOnFail, TallkEffectToCheck, TallkEffectDescription);
		HideIt();
	}
	if (FlirtButton)
	{
		FlirtButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::Flirt);
		FlirtButton->OnEffectAutoChecked.AddUObject(this, &UTQ_SelectorWidget::EffectHandling);
		FlirtButton->OnStatusAutoChecked.AddUObject(this, &UTQ_SelectorWidget::AskToPrintText);
		FlirtButton->SetAllStats(FlirtToCheck, FlirtStatRequirement, FlirtMessageOnSuccess,	//..
			FlirtMessageOnFail, FlirtEffectToCheck, FlirtEffectDescription);
		HideIt();
	}
	if (DrinkButton)
	{
		pipnek = false;
		DrinkButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::Drink);
		DrinkButton->OnEffectAutoChecked.AddUObject(this, &UTQ_SelectorWidget::EffectHandling);
		DrinkButton->OnStatusAutoChecked.AddUObject(this, &UTQ_SelectorWidget::AskToPrintText);
		DrinkButton->SetAllStats(DrinkToCheck, DrinkStatRequirement, DrinkMessageOnSuccess,	//..
			DrinkMessageOnFail, DrinkEffectToCheck, DrinkEffectDescription);
		HideIt();
	}
	if (EatButton)
	{
		pipnek = false;
		EatButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::Eat);
		EatButton->OnEffectAutoChecked.AddUObject(this, &UTQ_SelectorWidget::EffectHandling);
		EatButton->OnStatusAutoChecked.AddUObject(this, &UTQ_SelectorWidget::AskToPrintText);
		EatButton->SetAllStats(EatToCheck, EatStatRequirement, EatMessageOnSuccess,	//..
			EatMessageOnFail, EatEffectToCheck, EatEffectDescription);
		HideIt();

	}
	if (BiteButton)
	{
		BiteButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::Bite);
		BiteButton->OnEffectAutoChecked.AddUObject(this, &UTQ_SelectorWidget::EffectHandling);
		BiteButton->OnStatusAutoChecked.AddUObject(this, &UTQ_SelectorWidget::AskToPrintText);
		BiteButton->SetAllStats(BiteToCheck, BiteStatRequirement, BiteMessageOnSuccess,	//..
			BiteMessageOnFail, BiteEffectToCheck, BiteEffectDescription);
		HideIt();
	}
	if (KissButton)
	{
		KissButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::Kiss);
		KissButton->OnEffectAutoChecked.AddUObject(this, &UTQ_SelectorWidget::EffectHandling);
		KissButton->OnStatusAutoChecked.AddUObject(this, &UTQ_SelectorWidget::AskToPrintText);
		KissButton->SetAllStats(KissToCheck, KissStatRequirement, KissMessageOnSuccess,	//..
			KissMessageOnFail, KissEffectToCheck, KissEffectDescription);
		HideIt();
	}
	if (TakeButton)
	{
		TakeButton->OnClicked.AddDynamic(this, &UTQ_SelectorWidget::Take);
		TakeButton->OnEffectAutoChecked.AddUObject(this, &UTQ_SelectorWidget::EffectHandling);
		TakeButton->OnStatusAutoChecked.AddUObject(this, &UTQ_SelectorWidget::AskToPrintText);
		TakeButton->SetAllStats(TakeToCheck, TakeStatRequirement, TakeMessageOnSuccess,	//..
			TakeMessageOnFail, TakeEffectToCheck, TakeEffectDescription);
		HideIt();
	}
	if (Switcher)
	{
		Switcher->SetActiveWidgetIndex(1);
	}
	if (ButtonImage)
	{
		ButtonImage->SetBrushFromTexture(InButtonImage);
	}


	//}
	//FOnDestroyItemSignature OnDestroyItem;
	//OnDestroyItem.AddUObject()
	// 
	// Не удалая!! это для excel таблиц
	/*static ConstructorHelpers::FObjectFinder<UDataTable> BattleDataObject(TEXT("DataTable'/Game/DataTable/SelectorItemDataTable.SelectorItemDataTable'"));
	if (BattleDataObject.Succeeded())
	{
		ItemDataT = BattleDataObject.Object;
	}

	if (ItemDataT)
	{
		static const FString ContextString(TEXT("multyple Variables Context"));
		FSelectorItemData* TQDataT = ItemDataT->FindRow<FSelectorItemData>(RowName, ContextString, true);
		if (TQDataT)
		{//														/\
			//сеть значения... А лучше фигачь прямо в SetAll   //\\
			//													||
			//													||
		}
	}*/
}

UTQ_GameInstance* UTQ_SelectorWidget::GetGameInstance()
{
	const auto TQGameInst = Cast<UTQ_GameInstance>(GetWorld()->GetGameInstance());

	return TQGameInst;
}

void UTQ_SelectorWidget::UnHideIt()
{
	Switcher->SetActiveWidgetIndex(0);
	GetWorld()->GetTimerManager().SetTimer(Delay, this, &UTQ_SelectorWidget::HideIt, 10.0f, false);
}

void UTQ_SelectorWidget::HideIt()
{
	pipnek = true;
	Switcher->SetActiveWidgetIndex(1);
	GetWorld()->GetTimerManager().ClearTimer(Delay);
}

void UTQ_SelectorWidget::EffectHandling(FString In)
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

void UTQ_SelectorWidget::AskToPrintText(FString In)
{
		if (ServiseIF)
		{
			MessageReprint = In;
			PlayerHeandling(EEventResponseManager::Speach);
			const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
			HUD->AskToPrintText();
		}
}

void UTQ_SelectorWidget::YouCanPass()
{
	ForbidClick(true);
}

void UTQ_SelectorWidget::PlayerHeandling(EEventResponseManager WhatToDo)
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

void UTQ_SelectorWidget::ForbidClick(bool g)
{
	if (g)
	{
		ServiseIF = true;
		LickButton->SetBackgroundColor(FLinearColor::White);
		PushButton->SetBackgroundColor(FLinearColor::White);
		TallkButton->SetBackgroundColor(FLinearColor::White);
		FlirtButton->SetBackgroundColor(FLinearColor::White);
		DrinkButton->SetBackgroundColor(FLinearColor::White);
		EatButton->SetBackgroundColor(FLinearColor::White);
		BiteButton->SetBackgroundColor(FLinearColor::White);
		KissButton->SetBackgroundColor(FLinearColor::White);
		TakeButton->SetBackgroundColor(FLinearColor::White);
	}
	else
	{
		ServiseIF = false;
		LickButton->SetBackgroundColor(FLinearColor::Black);
		PushButton->SetBackgroundColor(FLinearColor::Black);
		TallkButton->SetBackgroundColor(FLinearColor::Black);
		FlirtButton->SetBackgroundColor(FLinearColor::Black);
		DrinkButton->SetBackgroundColor(FLinearColor::Black);
		EatButton->SetBackgroundColor(FLinearColor::Black);
		BiteButton->SetBackgroundColor(FLinearColor::Black);
		TakeButton->SetBackgroundColor(FLinearColor::Black);
		KissButton->SetBackgroundColor(FLinearColor::Black);
	}
}

void UTQ_SelectorWidget::EndExistance()
{
	SetVisibility(ESlateVisibility::Collapsed);

	GetGameInstance()->MapState[CreatorsName].IsHiddenObjectExist = false;
	GetGameInstance()->MapState[CreatorsName].IsObsticleVisible = false;

	OnDestroyItem.Broadcast();
}

void UTQ_SelectorWidget::Take()
{
	BaseInteractionEvent(FlirtButton->FinalResault, DestroyOnFlirt, GoToFlirtMap, FlirtEvent, "Take");

}

void UTQ_SelectorWidget::Eat()
{
	BaseInteractionEvent(FlirtButton->FinalResault, DestroyOnFlirt, GoToFlirtMap, FlirtEvent, "Eat");

}

void UTQ_SelectorWidget::Bite()
{
	BaseInteractionEvent(FlirtButton->FinalResault, DestroyOnFlirt, GoToFlirtMap, FlirtEvent, "Bite");

}

void UTQ_SelectorWidget::Kiss()
{
	BaseInteractionEvent(FlirtButton->FinalResault, DestroyOnFlirt, GoToFlirtMap, FlirtEvent, "Kiss");

}

void UTQ_SelectorWidget::Drink()
{
	BaseInteractionEvent(FlirtButton->FinalResault, DestroyOnFlirt, GoToFlirtMap, FlirtEvent, "Drink");

}

void UTQ_SelectorWidget::Flirt()
{
	BaseInteractionEvent(FlirtButton->FinalResault, DestroyOnFlirt, GoToFlirtMap, FlirtEvent, "Flirt");

}

void UTQ_SelectorWidget::Tallk()
{
	BaseInteractionEvent(TallkButton->FinalResault, DestroyOnTallk, GoToTallkMap, TallkEvent, "Tallk");

}

void UTQ_SelectorWidget::Push()
{
	BaseInteractionEvent(PushButton->FinalResault, DestroyOnPush, GoToPushMap, PushEvent, "Push");

}


void UTQ_SelectorWidget::Lick()
{
	BaseInteractionEvent(LickButton->FinalResault, DestroyOnLick, GoToLickMap, LickEvent, "Lick");

}


void UTQ_SelectorWidget::BaseInteractionEvent(bool FinalResault, bool IsDestroyOn, TSubclassOf<UUserWidget>& a, EEventResponseManager& b, FName ActionName)
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