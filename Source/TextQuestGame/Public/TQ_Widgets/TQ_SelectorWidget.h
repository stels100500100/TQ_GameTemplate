// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Engine/DataTable.h>
#include "Components/Image.h"
#include <Player/TQ_GameInstance.h>
#include <TQ_Utilitys/TQUtills.h>
#include <TQ_Widgets/TQ_AutoCheckButton.h>
#include "TQ_SelectorWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDestroyItemSignature);

class UTQ_AutoCheckButton;
class UButton;
class UWidgetSwitcher;
class UImage;
class UTQ_SpeakerWidget;
class USoundCue;


USTRUCT(BlueprintType)
struct FRandomEventStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomEvent", meta = (ClampMin = "1", ClampMax = "10"))
		int32 RandomEventChanse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomEvent")
		EEventResponseManager RandomEventAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomEvent")
		FString	RandomEventAnsver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable", meta = (ClampMin = "0.00", ClampMax = "1000.09"))
		float RandomEventDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomEvent")
		FText EHRRandomMessage;
};

USTRUCT(BlueprintType)
struct FDeathStruct
{
	GENERATED_USTRUCT_BODY()

		TSubclassOf<UUserWidget> DeathReason;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathWork")
		TSubclassOf<UUserWidget> DeathFromRandomEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathWork")
		TSubclassOf<UUserWidget> DeathFromWaiting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathWork")
		TSubclassOf<UUserWidget> DeathFromEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathWork", meta = (ToolTip = "Death caused by Damage from Hiting the wall and monsters damage at the Wagh screen"))
		TSubclassOf<UUserWidget> DeathFromDamageEvents;
};

USTRUCT(BlueprintType)
struct FWaitStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WiteAction")
		TArray<FString> WaitAnsver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WiteAction")
		TArray<FImageSequence> WaitImageSequence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WiteAction")
		FText EHRWaitMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WiteAction")
		EEventResponseManager WaitResoults;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WiteAction")
		FString DefaultWaitAnswer = "DefaultWaitAnswer";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WiteAction")
		EHiddenObjectHandling HiddenObjectAction;

	int32 WaitingSequenceStep;
};

USTRUCT(BlueprintType)
struct FExamActionStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExamEvent")
		FString	ExamActionAnsverOnSucsses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExamEvent")
		FString	ExamActionAnsverOnFail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExamEvent")
		FText EHRExamActionMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExamEvent")
		EEventResponseManager ExamAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExamEvent")
		int32 IntellectRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable", meta = (ClampMin = "0.00", ClampMax = "1000.09"))
		float ExamActionDamage;
};

USTRUCT(BlueprintType)
struct FNarrationStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration", meta = (ToolTip = "Text Message that apears at the screen construction, by the first entarance LevelScreen"))
		FString TextMessageForFirstEntarance = "Default value";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration", meta = (ToolTip = "Text Message that apears at the screen construction"))
		FString DefaultTextMessage = "Default value";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		FString DefaultEHRSpeachMessage = "DefaultEHR";
		FText EHRSpeachMessage;
		FString TextMessage = "Default value";
};

USTRUCT(BlueprintType)
struct FInventiryHandlingStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventiryHandling")
		int32 ItemToAdd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventiryHandling")
		FText EHRInventoryAddMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventiryHandling")
		int32 ItemToRemove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventiryHandling")
		FText EHRInventoryRemoveMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventiryHandling")
		bool DoUWannaToRemove;
};

USTRUCT(BlueprintType)
struct FCheckObstacleStruct
{
	GENERATED_USTRUCT_BODY()

		//CheckObstacle --ready
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling")
		bool TreatAsObsticle = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventiryHandling")
		bool DoUWannaToRemove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling", meta = (EditCondition = "!TreatAsObsticle"))
		FString	CheckObstacleActionAnsverOnSucsses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling", meta = (EditCondition = "!TreatAsObsticle"))
		FString	CheckObstacleActionAnsverOnFail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling", meta = (EditCondition = "!TreatAsObsticle"))
		EHiddenObjectHandling CheckObstacle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling")
		FText EHRRevealMessage;
};

USTRUCT(BlueprintType)
struct FDamageTableStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageTable", meta = (ClampMin = "0.00", ClampMax = "1000.09"), meta = (ToolTip = "Damage that Monster deals by the default"))
		float DefaultDamageToPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable", meta = (ClampMin = "0.00", ClampMax = "1000.09"))
		float HealAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable", meta = (ClampMin = "0.00", ClampMax = "1000.09"))
		float HealHungerAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable")
		bool HealthOrHunger = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable", meta = (ClampMin = "0.00", ClampMax = "1000.09"), meta = (ToolTip = "Damage that Monster deals by the default"))
		float DefaultHungerDamageToPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable", meta = (ClampMin = "0.00", ClampMax = "1000.09"), meta = (ToolTip = "Damage that Monster deals by the default"))
		TSubclassOf<UDamageType> HungerDamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable", meta = (ClampMin = "0.00", ClampMax = "1000.09"), meta = (ToolTip = "Damage that Monster deals by the default"))
		TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable")
		TArray<FString>  DamageAnsver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable")
		FText EHRDamageMessage;

	float DamageToPlayer;
	float HungerDamage;

};

USTRUCT(BlueprintType)
struct FEffectHandlingStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "EffectHandling")
		TMap<FString, FString> EffectCheckTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectHandling")
		FText EHREffectMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectHandling")
		FString EffectToFinde;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectHandling")
		FString EffectToAdd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectHandling")
		EEventResponseManager EffectResponce;
};

USTRUCT(BlueprintType)
struct FSoundSystem
{
	GENERATED_USTRUCT_BODY()

public:
	// Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundCue* DamageSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundCue* HealSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundCue* RevialSound;


	//Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		bool PlayNewMusic = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds", meta = (EditCondition = "PlayNewMusic", ToolTip = "Track number in play list of character"))
		int32 PlayNewMusicIndex;
};

USTRUCT(BlueprintType)
struct FEventSystems
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FNarrationStruct NarrationEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FDeathStruct DeathScreens;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FDamageTableStruct DamageTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FSoundSystem SoundSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FRandomEventStruct RandomEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FWaitStruct WaitingEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FExamActionStruct ExamEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FInventiryHandlingStruct InventiryHandlingEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FCheckObstacleStruct CheckObstacleEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FEffectHandlingStruct EffectHandlingEvent;
};

UCLASS()
class TEXTQUESTGAME_API UTQ_SelectorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FEventSystems SW_EventSystems;

	UFUNCTION(BlueprintCallable)
		void ForbidClick(bool g);
	UFUNCTION(BlueprintCallable)
		void SetCN(FName g) { CreatorsName = g; };
		FName CreatorsName;

		FOnDestroyItemSignature OnDestroyItem;
//private:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
		void EndExistance();
		UTQ_GameInstance* GetGameInstance();
		bool Existance = true;
		int32 InInstanceNumberSelector;

	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UWidgetSwitcher* Switcher;
public:
	//Buttons
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UButton* MainButton;
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UImage* ButtonImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTexture2D* InButtonImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FText EHRInventoryMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UDamageType> DamageType;


	//Lick
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTQ_AutoCheckButton* LickButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonLick")
		EStatusAutoCheck LickToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonLick")
		int32 LickStatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonLick", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOnLick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonLick")
		FString LickMessageOnSuccess = "Deffault Lick";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonLick")
		FString LickMessageOnFail = "Deffault Lick";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonLick")
		FString LickEffectToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonLick")
		FString LickEffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonLick")
		TSubclassOf<UUserWidget> GoToLickMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonLick")
		EEventResponseManager LickEvent;

	//Push
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTQ_AutoCheckButton* PushButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonPush")
		EStatusAutoCheck PushToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonPush")
		int32 PushStatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonPush", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOnPush;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonPush")
		FString PushMessageOnSuccess = "Deffault Push";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonPush")
		FString PushMessageOnFail = "Deffault Push";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonPush")
		FString PushEffectToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonPush")
		FString PushEffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonPush")
		TSubclassOf<UUserWidget> GoToPushMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonPush")
		EEventResponseManager PushEvent;

	//Tallk
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTQ_AutoCheckButton* TallkButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTallk")
		EStatusAutoCheck TallkToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTallk")
		int32 TallkStatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTallk", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOnTallk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTallk")
		FString TallkMessageOnSuccess = "Deffault Tallk";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTallk")
		FString TallkMessageOnFail = "Deffault Tallk";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTallk")
		FString TallkEffectToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTallk")
		FString TallkEffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTallk")
		TSubclassOf<UUserWidget> GoToTallkMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTallk")
		EEventResponseManager TallkEvent;

	//Flirt
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTQ_AutoCheckButton* FlirtButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonFlirt")
		EStatusAutoCheck FlirtToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonFlirt")
		int32 FlirtStatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonFlirt", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOnFlirt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonFlirt")
		FString FlirtMessageOnSuccess = "Deffault Flirt";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonFlirt")
		FString FlirtMessageOnFail = "Deffault Flirt";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonFlirt")
		FString FlirtEffectToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonFlirt")
		FString FlirtEffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonFlirt")
		TSubclassOf<UUserWidget> GoToFlirtMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonFlirt")
		EEventResponseManager FlirtEvent;

	//Drink
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTQ_AutoCheckButton* DrinkButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonDrink")
		EStatusAutoCheck DrinkToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonDrink")
		int32 DrinkStatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonDrink", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOnDrink;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonDrink")
		FString DrinkMessageOnSuccess = "Deffault Drink";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonDrink")
		FString DrinkMessageOnFail = "Deffault Drink";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonDrink")
		FString DrinkEffectToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonDrink")
		FString DrinkEffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonDrink")
		TSubclassOf<UUserWidget> GoToDrinkMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonDrink")
		EEventResponseManager DrinkEvent;
	//Eat
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTQ_AutoCheckButton* EatButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonEat")
		EStatusAutoCheck EatToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonEat")
		int32 EatStatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonEat", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOnEat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonEat")
		FString EatMessageOnSuccess = "Deffault Eat";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonEat")
		FString EatMessageOnFail = "Deffault Eat";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonEat")
		FString EatEffectToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonEat")
		FString EatEffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonEat")
		TSubclassOf<UUserWidget> GoToEatMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonEat")
		EEventResponseManager EatEvent;

	//Bite
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTQ_AutoCheckButton* BiteButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBite")
		EStatusAutoCheck BiteToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBite")
		int32 BiteStatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBite", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOnBite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBite")
		FString BiteMessageOnSuccess = "Deffault Bite";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBite")
		FString BiteMessageOnFail = "Deffault Bite";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBite")
		FString BiteEffectToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBite")
		FString BiteEffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBite")
		TSubclassOf<UUserWidget> GoToBiteMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBite")
		EEventResponseManager BiteEvent;

	//Kiss
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTQ_AutoCheckButton* KissButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonKiss")
		EStatusAutoCheck KissToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonKiss")
		int32 KissStatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonKiss", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOnKiss;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonKiss")
		FString KissMessageOnSuccess = "Deffault kiss";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonKiss")
		FString KissMessageOnFail = "Deffault kiss";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonKiss")
		FString KissEffectToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonKiss")
		FString KissEffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonKiss")
		TSubclassOf<UUserWidget> GoToKissMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonKiss")
		EEventResponseManager KissEvent;

	//Take
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		UTQ_AutoCheckButton* TakeButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		EStatusAutoCheck TakeToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		int32 TakeStatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOnTake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		FString TakeMessageOnSuccess = "Deffault Take";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		FString TakeMessageOnFail = "Deffault Take";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		FString TakeEffectToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		FString TakeEffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		TSubclassOf<UUserWidget> GoToTakeMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake", meta = (ToolTip = "True=RemoveItem /False=AddItem "))
		bool DoUWannaToRemoveT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		EEventResponseManager TakeEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		int32 ItemToRemove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonTake")
		int32 ItemToAdd;

		TSubclassOf<UUserWidget> GoToMap;

		FText EHRSpeachMessage;
		FText EHRDamageMessage;


		FTimerHandle Delay;
		FTimerHandle UseDelay;



	//TArray<FButtonInfo> BInfo;	// замени весь код кнопок на  



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TMap<FString, FString> EffectCheckTable;

		void PlayerHeandling(EEventResponseManager WhatToDo);
	UFUNCTION(BlueprintCallable)
		void HideIt();
	UFUNCTION(BlueprintCallable)
		void UnHideIt();
	UFUNCTION(BlueprintCallable)
		void EffectHandling(FString In);
	UFUNCTION(BlueprintCallable)
		void AskToPrintText(FString In);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		float DamageToPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		float HealAmount = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		float HealHungerAmount = 10.f;

		void YouCanPass();


	FString MessageReprint;
	bool ServiseIF = false; //rename
	bool pipnek = true; // my wife initiated this var. So i save original name for her :-)


private:
	void BaseInteractionEvent(bool FinalResault, bool IsDestracted, TSubclassOf<UUserWidget>& a, EEventResponseManager& b, FName ActionName);
	UFUNCTION()
		void Lick();
	UFUNCTION()
		void Push();
	UFUNCTION()
		void Tallk();
	UFUNCTION()
		void Flirt();
	UFUNCTION()
		void Drink();
	UFUNCTION()
		void Eat();
	UFUNCTION()
		void Bite();
	UFUNCTION()
		void Kiss();
	UFUNCTION(BlueprintCallable)
		void Take();
};
