// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/TQ_BaseLevelWidget.h"
#include "Engine/Engine.h"
#include <Blueprint/UserWidget.h>
#include <Components/Button.h>
#include "Components/Image.h"
#include "TQ_Components/TQ_InventoryComponent.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "Player/TQ_PlayerPawn.h"
#include <Kismet\GameplayStatics.h>
#include "TQ_Widgets/TQ_AutoCheckButton.h"
#include <TQ_Utilitys/TQUtills.h>
#include "Player/TQ_PlayerHUDWidget.h"
#include "TQ_Widgets/TQ_SpeakerWidget.h"
#include "TQ_Components/TQ_HealthComponent.h"
#include "Player/TQ_PlayerHUD.h"
#include "TQ_Widgets/TQ_SelectorWidget.h"
#include <Components/WidgetSwitcher.h>
#include <Components/VerticalBox.h>
#include "DamageTypes/HungerDamageType.h"
#include "DamageTypes/DefaultDamageType.h"
#include "Player/TQ_GameInstance.h"
#include "Sound/SoundCue.h"
#include "Components/CheckBox.h"
#include "TQ_Components/TQ_WalkmanComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BLW,All,All);

void UTQ_BaseLevelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	
	SetStartScrean();
	
	if (GetGameInstance()->MapState[FName(*GetName())].ShowTextMessageOnStart)
	{
		ForbidClick(false);
	}
	else
	{
		ForbidClick(true);
	}

	if (WaitButton)
	{
		WaitButton->OnClicked.AddDynamic(this, &UTQ_BaseLevelWidget::WaitAction);
	}


	if (ExaminButton)
	{
		ExaminButton->OnClicked.AddDynamic(this, &UTQ_BaseLevelWidget::ExamA);
	}

	if (TQBV_EventSystems.HiddenObjectHandlingParams.ToBeRevealed)
	{
		TQBV_EventSystems.HiddenObjectHandlingParams.ToBeRevealed.GetDefaultObject()->OnDestroyItem.AddUObject(this, &UTQ_BaseLevelWidget::DestroyItem);
	}

	if (BlockRepitingMessagesCheckbox)
	{
		BlockRepitingMessagesCheckbox->OnCheckStateChanged.AddDynamic(this, &UTQ_BaseLevelWidget::BlockRepitingMessages);
		GetGameInstance()->MapState[FName(*GetName())].ShowTextMessageOnStart;// = IWantAdditionalMessages;
		
		
		if (GetGameInstance()->MapState[FName(*GetName())].ShowTextMessageOnStart)
		{
			BlockRepitingMessagesCheckbox->SetCheckedState(ECheckBoxState::Checked);

		}
		else
		{
			BlockRepitingMessagesCheckbox->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}

	TQBV_EventSystems.RandomEvent.IsRandomEventNeeded = GetGameInstance()->MapState[FName(*GetName())].IsRandomEventNeeded;

	if (!LevelImage) return;
	
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (!HUD) return;
}

void UTQ_BaseLevelWidget::BlockRepitingMessages(bool Block)
{
	GetGameInstance()->MapState[FName(*GetName())].ShowTextMessageOnStart = Block;
}

void UTQ_BaseLevelWidget::WaitAction()
{
		if (IsButtonsActive)
		{
			TQBV_EventSystems.NarrationEvent.EHRSpeachMessage = TQBV_EventSystems.WaitingEvent.EHRWaitMessage;
			GetCharacter()->ApplayDamageToSelf(TQBV_EventSystems.DamageTable.HungerDamage, TQBV_EventSystems.DamageTable.HungerDamageType);
				RandomMachina();
			if (TQBV_EventSystems.WaitingEvent.WaitImageSequence.Num() == NULL)
			{
				if (TQBV_EventSystems.WaitingEvent.WaitAnsver.Num() == NULL)
				{
					TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.WaitingEvent.DefaultWaitAnswer;
					EventHandling(EEventResponseManager::Speach);
				}
				else
				{
					int32 WaitAnsverArrayMaxSize = TQBV_EventSystems.WaitingEvent.WaitAnsver.Num()-1;
					int32 RandomWaitAnsver = FMath::RandRange(0, WaitAnsverArrayMaxSize);
					TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.WaitingEvent.WaitAnsver[RandomWaitAnsver];
					EventHandling(EEventResponseManager::Speach);
					GetCharacter()->SetDeathWidget(TQBV_EventSystems.DeathScreens.DeathFromWaiting);
					EventHandling(TQBV_EventSystems.WaitingEvent.WaitResoults);
				}
			}
			else
			{
				int32 Length = TQBV_EventSystems.WaitingEvent.WaitImageSequence.Num();
				TQBV_EventSystems.WaitingEvent.WaitingSequenceStep++;
				if (TQBV_EventSystems.WaitingEvent.WaitingSequenceStep == Length)
				{
					TQBV_EventSystems.WaitingEvent.WaitingSequenceStep -= Length;
				}

				if (TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].HasEvent && !TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].bWantDerectioninfluence)
				{
					TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].Speech;
					if (TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].MapToGoFromImageSequence)
					{
						TQBV_EventSystems.NarrationEvent.GoToNextMap = TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].MapToGoFromImageSequence;
					}
					GetCharacter()->SetDeathWidget(TQBV_EventSystems.DeathScreens.DeathFromWaiting);

					EventHandling(TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].WhatToDo);
					EventObjectHandling(TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].WhatHiddenObjectDo);
				}

				//if (WaitImageSequence[step].Images=NULL) return;
				//checkf(WaitImageSequence[step].Images->IsAsset() , TEXT("There is no images"));

				LevelImage->SetBrushFromTexture(TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].Images, false);
			}
		}
}

void UTQ_BaseLevelWidget::RandomMachina()
{
	if (!TQBV_EventSystems.RandomEvent.IsDoOnce)
	{
		if (TQBV_EventSystems.RandomEvent.IsRandomEventNeeded)
		{
			TQBV_EventSystems.NarrationEvent.EHRSpeachMessage = TQBV_EventSystems.RandomEvent.EHRRandomMessage;
			int32 Probobility = FMath::RandRange(0, 10);
			if (TQBV_EventSystems.RandomEvent.RandomEventChanse > Probobility)
			{
				TQBV_EventSystems.DamageTable.DamageToPlayer = TQBV_EventSystems.RandomEvent.RandomEventDamage;
				if (TQBV_EventSystems.RandomEvent.RandomEventDamage == 0)
				{
					TQBV_EventSystems.DamageTable.DamageToPlayer = TQBV_EventSystems.DamageTable.DefaultDamageToPlayer;
				}
			}
			GetCharacter()->SetDeathWidget(TQBV_EventSystems.DeathScreens.DeathFromRandomEvent);
			TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.RandomEvent.RandomEventAnsver;
			EventHandling(TQBV_EventSystems.RandomEvent.RandomEventAction);
			if (TQBV_EventSystems.RandomEvent.DoOnce) TQBV_EventSystems.RandomEvent.IsDoOnce = true;
			if (TQBV_EventSystems.RandomEvent.AndThenNever)GetGameInstance()->MapState[FName(*GetName())].IsRandomEventNeeded = false;
		}
	}
}

void UTQ_BaseLevelWidget::SetStartScrean()
{
	if (TQBV_EventSystems.WaitingEvent.WaitImageSequence.Num() != 0)
	{
		LevelImage->SetBrushFromTexture(TQBV_EventSystems.WaitingEvent.WaitImageSequence[TQBV_EventSystems.WaitingEvent.WaitingSequenceStep].Images, true);
	}
	GetGameInstance()->MapState[FName(*GetName())].IsLevelAlreadyEntered ? TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.NarrationEvent.DefaultTextMessage : TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.NarrationEvent.TextMessageForFirstEntarance;
	TQBV_EventSystems.NarrationEvent.EHRSpeachMessage.FromString(TQBV_EventSystems.NarrationEvent.DefaultEHRSpeachMessage);
	TQBV_EventSystems.DamageTable.DamageToPlayer = TQBV_EventSystems.DamageTable.DefaultDamageToPlayer;
	TQBV_EventSystems.DamageTable.HungerDamage = TQBV_EventSystems.DamageTable.DefaultHungerDamageToPlayer;

	

	if (GetGameInstance()->MapState[FName(*GetName())].ShowTextMessageOnStart)
	{
		EventHandling(EEventResponseManager::Speach); 
	}

	if (GetGameInstance()->MapState[FName(*GetName())].IsHiddenObjectExist)
	{
		if (GetGameInstance()->MapState[FName(*GetName())].IsObsticleVisible || TQBV_EventSystems.HiddenObjectHandlingParams.TreatAsObsticle==true)
		{/* fa = CreateWidget<UTQ_SelectorWidget>(GetWorld(), TQBV_EventSystems.HiddenObjectHandlingParams.ToBeRevealed), fa->SetCN(FName(*GetName())), fa->AddToViewport(4), ItemPlaceHolder->AddChild(fa); */
		EventObjectHandling(EHiddenObjectHandling::Revial);
		}
	}

	const auto MusicPlayer = GetCharacter()->FindComponentByClass<UTQ_WalkmanComponent>();
	if (!MusicPlayer) return;
	if (TQBV_EventSystems.SoundSystem.PlayNewMusic) MusicPlayer->SetMusicIndexToPlay(TQBV_EventSystems.SoundSystem.PlayNewMusicIndex), MusicPlayer->PlayNewMusic();
	GetGameInstance()->MapState[FName(*GetName())].IsLevelAlreadyEntered = true;

}

void UTQ_BaseLevelWidget::DamagePlayer(bool ScreamRandomAnsvers)
{
	IsPlayerScreaming = ScreamRandomAnsvers;
	EventHandling(EEventResponseManager::Damage);
}

void UTQ_BaseLevelWidget::ApplyDamage()
{
	GetCharacter()->ApplayDamageToSelf(TQBV_EventSystems.DamageTable.DamageToPlayer, TQBV_EventSystems.DamageTable.DamageType);

	if (IsPlayerScreaming)
	{
		int32 DamageAnsverArrayMaxSize = TQBV_EventSystems.DamageTable.DamageAnsver.Num() - 1;

		int32 RandomDamageAnsver = FMath::RandRange(0, DamageAnsverArrayMaxSize);

		if (TQBV_EventSystems.DamageTable.DamageAnsver.Num()!=0)
		{
			TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.DamageTable.DamageAnsver[RandomDamageAnsver];
		}
		else
		{
			TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.DamageTable.DefaultDamageAnswer;
		}
	}

	GetCharacter()->SetDeathWidget(TQBV_EventSystems.DeathScreens.DeathFromDamageEvents);
}

void UTQ_BaseLevelWidget::EffectHandling(FString In)
{
	
		if (GetCharacter()->Effects.FindByKey(In))
		{
			FString* ji = TQBV_EventSystems.EffectHandlingEvent.EffectCheckTable.Find(In);
			TQBV_EventSystems.NarrationEvent.TextMessage = *ji;
			GetCharacter()->SetDeathWidget(TQBV_EventSystems.DeathScreens.DeathFromEffect);
			EventHandling(TQBV_EventSystems.EffectHandlingEvent.EffectResponce);
			

			//DamagePlayer(false);

		}
	

}

void UTQ_BaseLevelWidget::CheckObstacleAction(FString COA)
{

	TQBV_EventSystems.NarrationEvent.TextMessage = COA;

} //17,08,22 по работай над этим, я не помню как я это имплементировал*/

void UTQ_BaseLevelWidget::ExamA()
{

		if (IsButtonsActive)
		{
			const auto Character = Cast<ATQ_PlayerPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (GetGameInstance()->MapState[FName(*GetName())].IsHiddenObjectExist)
			{

				if (Character-> GetIntelegents() >= TQBV_EventSystems.ExamEvent.IntellectRequirement)
				{
					TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.ExamEvent.ExamActionAnsverOnSucsses;
					TQBV_EventSystems.NarrationEvent.GoToNextMap =TQBV_EventSystems.ExamEvent.MapToGoFromExamEvent;
					EventHandling(TQBV_EventSystems.ExamEvent.ExamAction);
				}
				else
				{
					TQBV_EventSystems.DamageTable.DamageToPlayer = TQBV_EventSystems.ExamEvent.ExamActionDamage;
					if (TQBV_EventSystems.ExamEvent.ExamActionDamage == 0)
					{
						TQBV_EventSystems.DamageTable.DamageToPlayer = TQBV_EventSystems.DamageTable.DefaultDamageToPlayer;
					}
					TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.ExamEvent.ExamActionAnsverOnFail;
					//EventHandling(ExamAction);
					TQBV_EventSystems.DamageTable.DamageToPlayer = TQBV_EventSystems.DamageTable.DefaultDamageToPlayer;
				}
			}
			else
			{
				TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.ExamEvent.ExamActionAnsverOnFail;
				EventHandling(EEventResponseManager::Speach);
			}
		}
	
}

void UTQ_BaseLevelWidget::DestroyItem()
{
	EventObjectHandling(EHiddenObjectHandling::HidePermanently);
	TQBV_EventSystems.HiddenObjectHandlingParams.TreatAsObsticle = false;
	UE_LOG(BLW,Display,TEXT("UTQ_BaseLevelWidget::DestroyItem"))
}

void UTQ_BaseLevelWidget::EventHandling(EEventResponseManager WhatToDo)
{


	
	//const auto Character = Cast<ATQ_PlayerPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//if (!Character) return;

	const auto HC = GetCharacter()->FindComponentByClass<UTQ_HealthComponent>();
	if (!HC) return;

	const auto Inventory = GetCharacter()->FindComponentByClass<UTQ_InventoryComponent>();
	if (!Inventory) return;

	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (!HUD) return;

	switch (WhatToDo)
	{

	case EEventResponseManager::Damage:

			ApplyDamage();
			GetCharacter()->SetDeathWidget(TQBV_EventSystems.DeathScreens.DeathFromDamageEvents);

		HUD->SetMessage(TQBV_EventSystems.NarrationEvent.TextMessage);
		HUD->SetEHRforMessage(TQBV_EventSystems.DamageTable.EHRDamageMessage);
		HUD->AskToPrintText();
		UGameplayStatics::SpawnSound2D(GetWorld(), TQBV_EventSystems.SoundSystem.DamageSound);
		UE_LOG(BLW,Display,TEXT("Damage"))
		break;

	case EEventResponseManager::AddEffect:

		GetCharacter()->AddEffect(TQBV_EventSystems.EffectHandlingEvent.EffectToAdd);
		//HUD->AddEffectMassage;
		HUD->SetMessage(TQBV_EventSystems.NarrationEvent.TextMessage);
		HUD->SetEHRforMessage(TQBV_EventSystems.EffectHandlingEvent.EHREffectMessage);
		HUD->AskToPrintText();

		break;

	case EEventResponseManager::InventoryHandling:

		HUD->SetMessage(TQBV_EventSystems.NarrationEvent.TextMessage);
		HUD->SetEHRforMessage(TQBV_EventSystems.InventiryHandlingEvents.EHRInventoryAddMessage);
		HUD->AskToPrintText();

		TQBV_EventSystems.InventiryHandlingEvents.DoUWannaToRemove							//
		  ?																					//
			Inventory->RemoveItem(TQBV_EventSystems.InventiryHandlingEvents.ItemToRemove)	//
		  :																					//
			Inventory->GiveItem(TQBV_EventSystems.InventiryHandlingEvents.ItemToAdd);		//
		break;

	case EEventResponseManager::Speach:
		HUD->SetEHRforMessage(TQBV_EventSystems.NarrationEvent.EHRSpeachMessage);
		HUD->SetMessage(TQBV_EventSystems.NarrationEvent.TextMessage);
		HUD->AskToPrintText();
		break;

	case EEventResponseManager::GoToNextMap:
		HUD->SetScreenLevelMap(TQBV_EventSystems.NarrationEvent.GoToNextMap);
		this->RemoveFromParent();
		CreateWidget<UUserWidget>(GetWorld(), TQBV_EventSystems.NarrationEvent.GoToNextMap)->AddToViewport(0);

		break;

	case EEventResponseManager::HiddenObjectHandling:
		EventObjectHandling(TQBV_EventSystems.HiddenObjectHandlingParams.CheckObstacle);
		HUD->SetMessage(TQBV_EventSystems.NarrationEvent.TextMessage);
		HUD->SetEHRforMessage(TQBV_EventSystems.HiddenObjectHandlingParams.EHRRevealMessage);
		HUD->AskToPrintText();
		break;

	case EEventResponseManager::Heal:
		TQBV_EventSystems.DamageTable.HealthOrHunger										//
			?																				//
			  HC->TryToAddHealth(TQBV_EventSystems.DamageTable.HealAmount)					//
			:																				//
			  HC->TryToAddHunger(TQBV_EventSystems.DamageTable.HealHungerAmount);			//
		HUD->SetMessage(TQBV_EventSystems.NarrationEvent.TextMessage);
		HUD->SetEHRforMessage(TQBV_EventSystems.DamageTable.EHRDamageMessage);
		HUD->AskToPrintText();
		UGameplayStatics::SpawnSound2D(GetWorld(), TQBV_EventSystems.SoundSystem.HealSound);
			break;

	case EEventResponseManager::Nothing:

		break;
	}
}

void UTQ_BaseLevelWidget::EventObjectHandling(EHiddenObjectHandling WhatToDo)
{
	switch (WhatToDo)
	{
	case EHiddenObjectHandling::Nothing:
		return;
		break;

	case EHiddenObjectHandling::Hide:
		ItemPlaceHolder->ClearChildren(), fa->RemoveFromParent();
		GetGameInstance()->MapState[FName(*GetName())].IsObsticleVisible = false;

		break;

	case EHiddenObjectHandling::HidePermanently:
		ItemPlaceHolder->ClearChildren(), fa->RemoveFromParent();
		GetGameInstance()->MapState[FName(*GetName())].IsHiddenObjectExist = false;
		GetGameInstance()->MapState[FName(*GetName())].IsObsticleVisible = false;


			break;

	case EHiddenObjectHandling::Revial:
		if (GetGameInstance()->MapState[FName(*GetName())].IsHiddenObjectExist)
		{
			UE_LOG(BLW, Display, TEXT("EHiddenObjectHandling::Revial"))
			TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.HiddenObjectHandlingParams.CheckObstacleActionAnsverOnSucsses;
			fa = CreateWidget<UTQ_SelectorWidget>(GetWorld(), TQBV_EventSystems.HiddenObjectHandlingParams.ToBeRevealed), fa->SetCN(FName(*GetName())), fa->AddToViewport(4), ItemPlaceHolder->AddChild(fa);
			fa->OnDestroyItem.AddUObject(this, &UTQ_BaseLevelWidget::DestroyItem);
			GetGameInstance()->MapState[FName(*GetName())].IsObsticleVisible = true;
			UGameplayStatics::SpawnSound2D(GetWorld(), TQBV_EventSystems.SoundSystem.RevivalSound);
		}
		else
		{
			TQBV_EventSystems.NarrationEvent.TextMessage = TQBV_EventSystems.HiddenObjectHandlingParams.CheckObstacleActionAnsverOnFail;
		}

		break;

	}
}

UTQ_GameInstance* UTQ_BaseLevelWidget::GetGameInstance()
{
	const auto TQGameInst = Cast<UTQ_GameInstance>(GetWorld()->GetGameInstance());
	if (!TQGameInst) return NULL;

	return TQGameInst;
}

ATQ_PlayerPawn* UTQ_BaseLevelWidget::GetCharacter()
{
	const auto TQCharacter = Cast<ATQ_PlayerPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!TQCharacter) return NULL;

	return TQCharacter;
}

void UTQ_BaseLevelWidget::Travel(TSubclassOf<UUserWidget>& TravelTo)
{
	if (IsButtonsActive)
	{
		if (*TravelTo == nullptr)
		{
			DamagePlayer(true);
		}
		else
		{
			EventHandling(EEventResponseManager::GoToNextMap);
		}
	}
}

void UTQ_BaseLevelWidget::SetUPEvents()
{
	if (Viy)
	{
		RandomMachina();
		if (!TQBV_EventSystems.EffectHandlingEvent.EffectToFinde.IsEmpty())
		{
			EffectHandling(TQBV_EventSystems.EffectHandlingEvent.EffectToFinde);

			Viy = false;
		};
		if (!TQBV_EventSystems.EffectHandlingEvent.EffectToAdd.IsEmpty())
		{
			EventHandling(EEventResponseManager::AddEffect);
		}
	}
}

void UTQ_BaseLevelWidget::ForbidClick(bool IsClickForbidden)
{
	if (IsClickForbidden)
	{
			IsButtonsActive = false;
		//EventSystem-> ;

		WaitButton->SetBackgroundColor(FLinearColor::White);
		ExaminButton->SetBackgroundColor(FLinearColor::White);
	}
	else
	{
			IsButtonsActive = true;

		WaitButton->SetBackgroundColor(FLinearColor::Black);
		ExaminButton->SetBackgroundColor(FLinearColor::Black);
	}
}
