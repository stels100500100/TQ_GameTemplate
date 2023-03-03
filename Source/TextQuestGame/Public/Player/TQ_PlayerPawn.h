// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TQ_Widgets/TQ_SpeakerWidget.h"
#include "TQ_Widgets/BattleWidgets/DeathWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "TQ_PlayerPawn.generated.h"

class UTQ_SpeakerWidget;
class UUserWidget;
class UTQ_HealthComponent;
class UTQ_InventoryComponent;
class UTQ_WalkmanComponent;
class UTQ_EventExecuterComponent;

USTRUCT(BlueprintType)
struct FTQ_PlayerStat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Luck = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Strength = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Intelegents = 0;
};

UCLASS()
class TEXTQUESTGAME_API ATQ_PlayerPawn : public ACharacter
{
	GENERATED_BODY()

public:
	ATQ_PlayerPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	// Damage
	UFUNCTION()
		void ApplayDamageToSelf(float DamageModifire, TSubclassOf<UDamageType> DamagEvent);

	// Getters
	UFUNCTION()
		int32 GetLuck() const { return PlayerStat.Luck; }
	UFUNCTION()
		int32 GetStrength() const { return PlayerStat.Strength; }
	UFUNCTION()
		int32 GetIntelegents() const { return PlayerStat.Intelegents; }

	UFUNCTION()
		TArray<FString> GetEffects() const { return Effects; };

	// Setters
	UFUNCTION(BlueprintCallable)
		void SetLuck(int32 SetLuck) { PlayerStat.Luck = SetLuck; }
	UFUNCTION(BlueprintCallable)
		void SetStrength(int32 SetStrength) { PlayerStat.Strength = SetStrength; }
	UFUNCTION(BlueprintCallable)
		void SetIntellegents(int32 SetIntellegents) { PlayerStat.Intelegents = SetIntellegents; }
	UFUNCTION(BlueprintCallable)
		void SetDeathWidget(TSubclassOf<UUserWidget> SetDeathWidget) { DeathWidget = SetDeathWidget; }
	UFUNCTION(BlueprintCallable)
		void SetEffects(TArray <FString>EffectsToSet) { Effects = EffectsToSet; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UDeathWidget> DeathWidget;
		UDeathWidget* DefaultDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame", meta = (ToolTip = "Widget that will be created if Death reason in not seted"))
		TSubclassOf<UDeathWidget> DefaultDeathWidget;
		UDeathWidget* DDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TSubclassOf<UTQ_SpeakerWidget> SpiackerWidget;
		UTQ_SpeakerWidget* WidgetToSpeak;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame")
		TArray<FString> Effects;

	UFUNCTION()
		void AddEffect(FString AddIn);
	UFUNCTION()
		void RemoveEffect(FString CutIn);

private:
	UFUNCTION()
		void OnDeath();

	UPROPERTY(EditAnywhere, Category = "TQGame")
		FTQ_PlayerStat PlayerStat;
	
	/*UPROPERTY(EditAnywhere)
		int32 Luck = 0;
	UPROPERTY(EditAnywhere)
		int32 Strength = 0;
	UPROPERTY(EditAnywhere)
		int32 Intelegents = 0;*/
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UTQ_HealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UTQ_InventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UTQ_WalkmanComponent* WalkManComponent;

};
