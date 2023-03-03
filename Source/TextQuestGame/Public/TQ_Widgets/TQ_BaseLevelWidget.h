// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include <TQ_Utilitys/TQUtills.h>
#include "Components/CheckBox.h"
#include <Player/TQ_PlayerPawn.h>
#include <Player/TQ_GameInstance.h>
#include "TQ_Widgets/TQ_InteractivObjectWidget.h"
#include "TQ_SelectorWidget.h"
#include "TQ_BaseLevelWidget.generated.h"

class UButton;
class UImage;
class UTexture2D;
class USoundCue;
class UTQ_SpeakerWidget;
class UTQ_AutoCheckButton;
class UTQ_PlayerHUDWidget;
class USoundCue;
class UDataTable;
class UTQ_HealthComponent;
class UTQ_SelectorWidget;
class UVerticalBox;
class USoundCue;

USTRUCT(BlueprintType)
struct FRandomEventStructBL
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Tooltip= "Makes Random event callable one time, but resets after screen reloading "))
		bool DoOnce=false;
		bool IsDoOnce = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "DoOnce", Tooltip = "Makes Random event callable only one time"))
		bool AndThenNever = false;
		bool IsRandomEventNeeded =false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomEvent", meta = (ClampMin = "1", ClampMax = "10"))
		int32 RandomEventChanse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomEvent")
		EEventResponseManager RandomEventAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomEvent", meta = (Tooltip="Text Message that appears when RandomEvent was triggered"))
		FString	RandomEventAnsver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable", meta = (ClampMin = "0.00", ClampMax = "1000.09"))
		float RandomEventDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomEvent")
		FText EHRRandomMessage;
};

USTRUCT(BlueprintType)
struct FDeathStructBL
{
	GENERATED_USTRUCT_BODY()

		TSubclassOf <UUserWidget> DeathReason;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathWork")
		TSubclassOf <UUserWidget> DeathFromRandomEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathWork")
		TSubclassOf <UUserWidget> DeathFromWaiting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathWork")
		TSubclassOf <UUserWidget> DeathFromEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathWork")
		TSubclassOf <UUserWidget> DeathFromDamageEvents;
};

USTRUCT(BlueprintType)
struct FWaitStructBL
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WiteAction")
		TArray<FString> WaitAnsver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WiteAction")
		TArray<FImageSequence> WaitImageSequence ;
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
struct FExamActionStructBL
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExamEvent")
		TSubclassOf<UUserWidget> MapToGoFromExamEvent;
};

USTRUCT(BlueprintType)
struct FNarrationStructBL
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration", meta = (ToolTip = "Text Message that apears at the screen construction, by the first entarance LevelScreen"))
		FString TextMessageForFirstEntarance = "Default value";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration", meta = (ToolTip = "Text Message that apears at the screen construction"))
		FString DefaultTextMessage = "Default value";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		FString DefaultEHRSpeachMessage = "DefaultEHR";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TSubclassOf<UUserWidget> GoToNextMap;
	FText EHRSpeachMessage;
	FString TextMessage = "Default value";


};

USTRUCT(BlueprintType)
struct FInventiryHandlingStructBL
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
struct FCheckObstacleStructBL
{
	GENERATED_USTRUCT_BODY()

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling")
		bool TreatAsObsticle = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling", meta = (EditCondition = "!TreatAsObsticle"))
		FString	CheckObstacleActionAnsverOnSucsses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling", meta = (EditCondition = "!TreatAsObsticle"))
		FString	CheckObstacleActionAnsverOnFail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling", meta = (EditCondition = "!TreatAsObsticle"))
		EHiddenObjectHandling CheckObstacle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <UTQ_InteractivObjectWidget> ToBeRevealed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HiddenObjectHandling")
		FText EHRRevealMessage;
};

USTRUCT(BlueprintType)
struct FDamageTableStructBL
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
		FString DefaultDamageAnswer = "Default answer";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTable")
		FText EHRDamageMessage;

	float DamageToPlayer;
	float HungerDamage;

};

USTRUCT(BlueprintType)
struct FEffectHandlingStructBL
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
struct FSoundSystemBL
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
struct FEventSystemsBL
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FNarrationStructBL NarrationEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FDeathStructBL DeathScreens;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FDamageTableStructBL DamageTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FSoundSystemBL SoundSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FRandomEventStructBL RandomEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FWaitStructBL WaitingEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FExamActionStructBL ExamEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FInventiryHandlingStructBL InventiryHandlingEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FCheckObstacleStructBL HiddenObjectHandlingParams;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EventS")
		FEffectHandlingStructBL EffectHandlingEvent;

};

UCLASS()
class TEXTQUESTGAME_API UTQ_BaseLevelWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeOnInitialized() override;

	virtual void SetStartScrean();

	UFUNCTION(BlueprintCallable)
		void EventHandling(EEventResponseManager WhatToDo);

	UFUNCTION(BlueprintCallable)
		void EventObjectHandling(EHiddenObjectHandling WhatToDo);

	UFUNCTION(BlueprintCallable)
		void Travel(TSubclassOf<UUserWidget>& TravelTo);

	UFUNCTION(BlueprintCallable)
		void EffectHandling(FString In);

	UFUNCTION(BlueprintCallable)
		virtual void SetUPEvents(); // fireoff in BP

	UFUNCTION(BlueprintCallable)
		virtual void ForbidClick(bool g);

	UFUNCTION()
		virtual void DestroyItem();

	UFUNCTION(BlueprintCallable)
		FString GetTextMessage() { return TQBV_EventSystems.NarrationEvent.TextMessage; }
		
	UFUNCTION(BlueprintCallable)
		TSubclassOf<UUserWidget> GetGoToNextMap() const { return TQBV_EventSystems.NarrationEvent.GoToNextMap; };

	UFUNCTION(BlueprintCallable)
		void ExamA();

	UFUNCTION()
		void DamagePlayer(bool ScreamRandomAnsvers);

	UFUNCTION(BlueprintCallable)
		void ApplyDamage();

	UFUNCTION(BlueprintCallable)
		void RandomMachina();

	UFUNCTION(BlueprintCallable)
		void WaitAction();

	UFUNCTION(BlueprintCallable)
		void CheckObstacleAction(FString COA);

	UFUNCTION(BlueprintCallable)
		void BlockRepitingMessages(bool Block);

		UTQ_GameInstance* GetGameInstance();

		ATQ_PlayerPawn* GetCharacter();


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		FEventSystemsBL TQBV_EventSystems;

	UPROPERTY(meta = (BindWidget))
		UButton* WaitButton;

	UPROPERTY(meta = (BindWidget))
		UButton* ExaminButton;

	UPROPERTY( meta = (BindWidget))
		UCheckBox* BlockRepitingMessagesCheckbox;

	UPROPERTY( meta = (BindWidget))
		UVerticalBox* ItemPlaceHolder;
		UTQ_SelectorWidget* fa;

	//Image Handling
	UPROPERTY( meta = (BindWidget))
		UImage* LevelImage;
		UTexture2D* Level;


	bool Viy = true; // rename а лучше удали! это не нужно
	bool IsButtonsActive = false;
	bool IsPlayerScreaming;

	//Defaults
	FString DefaultWaitingAnswer = "DefaultWaitingAnswer";
	FString DefaultExamAnswer = "DefaultExamAnswer";
	FString DefaultRandomAnswer = "DefaultRandomAnswer";
};

