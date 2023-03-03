// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Engine/DataTable.h>
#include "Components/Image.h"
#include <Player/TQ_GameInstance.h>
#include <TQ_Utilitys/TQUtills.h>
#include <TQ_Widgets/TQ_AutoCheckButton.h>
#include "TQ_InteractivObjectWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDestroyItemSignature);

class UTQ_AutoCheckButton;
class UButton;
class UWidgetSwitcher;
class UImage;
class UTQ_SpeakerWidget;
class USoundCue;

USTRUCT(BlueprintType)
struct FButtonInfo
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTQ_AutoCheckButton* ACh_Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStatusAutoCheck BInfo_ToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BInfo_StatRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonInfo", meta = (Tooltip = "If True= destroy item on success, if False item will stay"))
		bool DestroyOn_BInfo_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonInfo")
		FString BInfo_MessageOnSuccess = "BInfo_Deffault_MessageOnSuccess";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonInfo")
		FString BInfo_MessageOnFail = "BInfo_Deffault_MessageOnFail";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BInfo_EffectToCheck = "BInfo_Deffault_";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BInfo_EffectDescription = "BInfo_Deffault_TakeEffectDescription";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> GoTo_BInfo_Map;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "True=RemoveItem /False=AddItem "))
		bool DoUWannaToRemoveT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEventResponseManager BInfo_Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemToRemove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemToAdd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ActionName = "DEFAULT_Action_Name";
};


USTRUCT(BlueprintType)
struct FRandomEventStructt
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
struct FDeathStructt
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
struct FWaitStructt
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
struct FExamActionStructt
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
struct FNarrationStructt
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
struct FInventiryHandlingStructt
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
struct FCheckObstacleStructt
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
struct FDamageTableStructt
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
struct FEffectHandlingStructt
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
struct FSoundSystemt
{
	GENERATED_USTRUCT_BODY()

public:
	// Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundCue* DamageSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundCue* HealSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundCue* RevivalSound;


	//Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		bool PlayNewMusic = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds", meta = (EditCondition = "PlayNewMusic", ToolTip = "Track number in play list of character"))
		int32 PlayNewMusicIndex;
};

USTRUCT(BlueprintType)
struct FEventSystemst
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FNarrationStructt NarrationEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FDeathStructt DeathScreens;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FDamageTableStructt DamageTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FSoundSystemt SoundSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FRandomEventStructt RandomEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FWaitStructt WaitingEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FExamActionStructt ExamEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FInventiryHandlingStructt InventiryHandlingEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FCheckObstacleStructt CheckObstacleEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FEffectHandlingStructt EffectHandlingEvent;
};

UCLASS()
class TEXTQUESTGAME_API UTQ_InteractivObjectWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FEventSystemst SW_EventSystems;

	UFUNCTION(BlueprintCallable)
		void ForbidClick(bool g);


	FOnDestroyItemSignature OnDestroyItem;
	//private:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
		void EndExistance();
		UTQ_GameInstance* GetGameInstance();
		bool Existance = true;
		int32 InInstanceNumberSelector;

	UFUNCTION(BlueprintCallable)
		void SetCN(FName g) { CreatorsName = g; };
		FName CreatorsName;

	UWidgetSwitcher* Switcher;
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_9;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_11;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_13;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_14;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		FButtonInfo CustomAction_15;
		int32 ItemToRemove;
		int32 ItemToAdd;
	

	TSubclassOf<UUserWidget> GoToMap;

	FText EHRSpeachMessage;
	FText EHRDamageMessage;


	FTimerHandle Delay;
	FTimerHandle UseDelay;


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


	FString MessageReprint;
	bool ServiseIF = false; //rename
	bool pipnek = true; // my wife initiated this var. So i save original name for her :-)


private:

	void YouCanPass();
	void BaseInteractionEvent(bool FinalResault, bool IsDestracted, TSubclassOf<UUserWidget>& a, EEventResponseManager& b, FName ActionName);
	UFUNCTION()
		void Custom_1();
	UFUNCTION()
		void Custom_2();
	UFUNCTION()
		void Custom_3();
	UFUNCTION()
		void Custom_4();
	UFUNCTION()
		void Custom_5();
	UFUNCTION()
		void Custom_6();
	UFUNCTION()
		void Custom_7();
	UFUNCTION()
		void Custom_8();
	UFUNCTION()
		void Custom_9();
	UFUNCTION()
		void Custom_10();
	UFUNCTION()
		void Custom_11();
	UFUNCTION()
		void Custom_12();
	UFUNCTION()
		void Custom_13();
	UFUNCTION()
		void Custom_14();
	UFUNCTION()
		void Custom_15();
};
