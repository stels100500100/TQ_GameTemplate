// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TQ_Widgets/TQ_BaseLevelWidget.h"
#include <TQ_Components/Inventory/TQ_InventoryStruct.h>
#include <TQ_Widgets/TQ_BaseLevelWidget.h>
#include "TQ_BattleLevelWidget.generated.h"

class UProgressBar;
class UWidgetAnimation;
class UDataTable;
class UButton;

USTRUCT(BlueprintType)
struct FBattleAction
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetAnimation* AnimationToPlay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 APCoast;

		FText MessageToShow;
};

UCLASS()
class TEXTQUESTGAME_API UTQ_BattleLevelWidget : public UTQ_BaseLevelWidget
{
	GENERATED_BODY()
protected:

	virtual void NativeOnInitialized() override;

	virtual void ForbidClick(bool g) override;


	UPROPERTY(meta = (BindWidget))
		UProgressBar* EnamyHealth;

	UPROPERTY(meta = (BindWidget))
		UButton* MakeTurnButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ActionPointsDisplay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Battlefield", meta = (ToolTip = "Animation of, Player been damaged."))
		UWidgetAnimation* AttackAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Battlefield", meta = (ToolTip = "Animation of, Player been damaged."))
		UWidgetAnimation* MonsterBlockAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Battlefield", meta = (ToolTip = "Animation of, Monster been damaged."))
		UWidgetAnimation* DamageAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Battlefield")
		UWidgetAnimation* VictoryAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Battlefield")
		UWidgetAnimation* FleeFeiledAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Battlefield")
		UWidgetAnimation* FleeSuccessAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Battlefield")
		UWidgetAnimation* YourTurnAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Battlefield")
		UWidgetAnimation* TurnEnamyAnimation;

	FTimerHandle FleeTimer;
	FTimerHandle VictoryTimer;

	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const { return MonsterHealth / MonsterMaxHealth; }

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield", meta = (ToolTip = "Damage that Monster deals by the default"))
	//	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield", meta = (ToolTip = "Measures requirements ageinst Intelegents + Luck"))
		int32 FleeRequirment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield", meta = (ToolTip = "Measures how's turn first"))
		int32 TurnRandomRequirment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield", meta = (ClampMin = "0.0", ClampMax = "10000.0"))
		float MonsterHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield", meta = (ClampMin = "0.0", ClampMax = "10000.0"))
		float MonsterMaxHealth;

	FTimerHandle AnimationEnd;

	FTimerHandle DelayA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield", meta = (ClampMin = "0"))
		int32 ActionPoints = 4;
private:

	UFUNCTION(BlueprintCallable)
		void SetStartScreen();
	UFUNCTION(BlueprintCallable)
		void MakeTurn();
	UFUNCTION(BlueprintCallable)
		void AttackAction();
	UFUNCTION(BlueprintCallable)
		void BlockAction();
	UFUNCTION(BlueprintCallable)
		void FleeAction();
	UFUNCTION(BlueprintCallable)
		void DamageForMonster();
	UFUNCTION(BlueprintCallable)
		void DamageForPlayer(float DamageModifire);


	//Damage
	void CkookDamage(float DamageModifire);
	float ProcessDamage(UTQ_InventoryComponent* Inventory);
	float MakeDamage();


	//Defence
	float ProcessDefence(UTQ_InventoryComponent* Inventory);
	float MakeDefence();

	//End Fight
	void Victory();
	void AfterVictory();
	void YourTurn();
	void EnamyTurn();
	bool ForbidFight = false;

	//Getters
	ATQ_PlayerPawn* GetCharacter();
	UTQ_InventoryComponent* GetInventory();

	UPROPERTY(meta = (BindWidget))
		UButton* AttackButton;

	UPROPERTY(meta = (BindWidget))
		UButton* BlockButton;

	UPROPERTY(meta = (BindWidget))
		UButton* FleeButton;


public:
	UFUNCTION(BlueprintCallable)
		void JustDamage();
	void RedrawActionPoints();
	void MakeBattleActionWidget(FBattleAction In);
	void DeleteBattleActionWidget();





	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield", meta = (ClampMin = "0.0", ClampMax = "10.0"), meta = (ToolTip = "0= monster always blocks attack, 10 = monster never blocks attack "))
		int32 Monster_s_BlockFaillChanse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield")
		TSubclassOf<UUserWidget> DeathScrean;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield")
		float DelayPrint = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield", meta = (ToolTip = "Table of effects that force monster to take more damage"))
		TMap<FString, float> EffectsToCheckAndDamagMonster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield", meta = (ToolTip = "Table of effects that force player character take more damage"))
		TMap<FString, float> EffectsToCheckAndDamagPlayer;

	UPROPERTY(BlueprintReadWrite, Category = "Battlefield", meta = (ToolTip = "Effects carried by the player character"))
		TArray<FString>EffectsOnCharacter;

	UPROPERTY(BlueprintReadWrite)
		TArray <int32> IIP_InCharactersPocket; 
	
	UPROPERTY(BlueprintReadWrite)
		FText Attack;
	UPROPERTY(BlueprintReadWrite)
		FText Block;
		FText A;

	UPROPERTY(BlueprintReadWrite)
		TArray<FBattleAction> TurnArrayState;
		int32 TurnArrayCount = 0;

	UPROPERTY(BlueprintReadWrite)
		FBattleAction AttackBA;

	UPROPERTY(BlueprintReadWrite)
		FBattleAction BlockBA;

	UPROPERTY(BlueprintReadWrite)
		FBattleAction MonsterBlockBA;
};

