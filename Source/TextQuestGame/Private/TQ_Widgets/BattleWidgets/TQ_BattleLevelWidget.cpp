// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/BattleWidgets/TQ_BattleLevelWidget.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Animation/WidgetAnimation.h>
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "Engine/Engine.h"

#include <Player/TQ_PlayerHUD.h>
#include <TQ_Components/Inventory/TQ_InventoryStruct.h>
#include <TQ_Components/TQ_InventoryComponent.h>


DEFINE_LOG_CATEGORY_STATIC(TQ_BattleLevelWidgetLog,All,All)

void UTQ_BattleLevelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GetCharacter()->SetDeathWidget(DeathScrean);

	if (AttackButton)
	{
		AttackButton->OnClicked.AddDynamic(this, &UTQ_BattleLevelWidget::AttackAction);
	}
	if (BlockButton)
	{
		BlockButton->OnClicked.AddDynamic(this, &UTQ_BattleLevelWidget::BlockAction);
	}
	if (FleeButton)
	{
		FleeButton->OnClicked.AddDynamic(this, &UTQ_BattleLevelWidget::FleeAction);
	}
	if (EnamyHealth)
	{
		EnamyHealth->SetFillColorAndOpacity(FLinearColor::Red);
	}
	if (WaitButton)
	{
		WaitButton->OnClicked.AddUniqueDynamic(this, &UTQ_BattleLevelWidget::JustDamage); 
	}
	if (MakeTurnButton)
	{
		MakeTurnButton->OnClicked.AddDynamic(this, &UTQ_BattleLevelWidget::MakeTurn);

	}
	if (ActionPointsDisplay)
	{
		ActionPointsDisplay->SetText(FText::FromString(FString::FromInt(ActionPoints)));
	}
	 TQBV_EventSystems.WaitingEvent.WaitingSequenceStep = 0;

	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	HUD->ACS.AddUObject(this, &UTQ_BattleLevelWidget::DeleteBattleActionWidget);



	//SetStartScreen();
	// Не удалая!! это для excel таблиц
	/*static ConstructorHelpers::FObjectFinder<UDataTable> BattleDataObject(TEXT("DataTable'/Game/DataTable/BattlefieldDataTable.BattlefieldDataTable'"));
	if(BattleDataObject.Succeeded())
	{
		WaaghDataT = BattleDataObject.Object;
	}

	if (WaaghDataT)
	{
		static const FString ContextString(TEXT("multyple Variables Context"));
		FBattlefieldData* TQDataT = WaaghDataT->FindRow<FBattlefieldData>(RowName, ContextString, true);
		if (TQDataT)
		{
			Damage=TQDataT->Damage;
			FleeRequirment = TQDataT->FleeRequirment;
			MonsterHealth = TQDataT->MonsterHealth;
			MonsterMaxHealth = TQDataT->MonsterMaxHealth;
			EffectsToCheckAndDamagPlayer = TQDataT->EffectsToCheckAndDamagPlayerTable;
			EffectsToCheckAndDamagMonster = TQDataT->EffectsToCheckAndDamagMonsterTable;
		}
	}*/
}

void UTQ_BattleLevelWidget::MakeBattleActionWidget(FBattleAction In)
{
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	HUD->SetPronouncement(A);
	HUD->SetActionPointsScore(In.APCoast);
	HUD->SetAttackMessage();
	ActionPoints += In.APCoast;
	RedrawActionPoints();
}

void UTQ_BattleLevelWidget::DeleteBattleActionWidget()
{
	ActionPoints -= TurnArrayState[TurnArrayCount].APCoast;
	RedrawActionPoints();
	TurnArrayState.RemoveAt(TurnArrayCount);
}

void UTQ_BattleLevelWidget::ForbidClick(bool g)
{
	if (g)
	{
		IsButtonsActive = true;

		AttackButton->SetBackgroundColor(FLinearColor::White);
		BlockButton->SetBackgroundColor(FLinearColor::White);
		FleeButton->SetBackgroundColor(FLinearColor::White);

		WaitButton->SetBackgroundColor(FLinearColor::White);
		ExaminButton->SetBackgroundColor(FLinearColor::White);
	}
	else
	{
		IsButtonsActive = false;

		AttackButton->SetBackgroundColor(FLinearColor::Black);
		BlockButton->SetBackgroundColor(FLinearColor::Black);
		FleeButton->SetBackgroundColor(FLinearColor::Black);

		WaitButton->SetBackgroundColor(FLinearColor::Black);
		ExaminButton->SetBackgroundColor(FLinearColor::Black);
	}

}

void UTQ_BattleLevelWidget::SetStartScreen()
{
	int32 RandomChance = FMath::RandRange(0, 10);
	if (RandomChance >= TurnRandomRequirment)
	{
		PlayAnimationForward(DamageAnimation);
	}
	else
	{
		DamageForPlayer(TQBV_EventSystems.DamageTable.DefaultDamageToPlayer);
	}
}

void UTQ_BattleLevelWidget::AttackAction()
{
	int32 Probobility = FMath::RandRange(0, 10);
	if (Monster_s_BlockFaillChanse > Probobility)
	{
		if (ActionPoints != 0)
		{
			A = Attack;
			TurnArrayState.Add(AttackBA);
			MakeBattleActionWidget(AttackBA);
		}
	}
	else
	{
		if (ActionPoints != 0)
		{
			A = Attack;
			TurnArrayState.Add(MonsterBlockBA);
			MakeBattleActionWidget(AttackBA);
		}
	}


	//StaminaScore -= 1;
	/*if (StaminaScore != 0)
	{
		Gek();
		ForbidClick(false);
		PlayAnimationForward(DamageAnimation);
		GetWorld()->GetTimerManager().SetTimer(AnimationEnd, this, &UWagh_TQ::EnamyTurn, DamageAnimation->GetEndTime(), false);
	}*/
}

void UTQ_BattleLevelWidget::BlockAction()
{
	A = Block;
	TurnArrayState.Add(BlockBA);
	MakeBattleActionWidget(BlockBA);

}

void UTQ_BattleLevelWidget::FleeAction()
{
	if (FleeRequirment <= GetCharacter()->GetLuck() + GetCharacter()->GetIntelegents())
	{
		PlayAnimationForward(FleeSuccessAnimation);
		GetWorld()->GetTimerManager().SetTimer(FleeTimer, this, &UTQ_BattleLevelWidget::AfterVictory, FleeSuccessAnimation->GetEndTime(), false);
	}
	else
	{
		PlayAnimationForward(FleeFeiledAnimation);
		DamageForPlayer(TQBV_EventSystems.DamageTable.DefaultDamageToPlayer / 4);
	}
}

void UTQ_BattleLevelWidget::Victory()
{
	ForbidFight = true;
	PlayAnimationForward(VictoryAnimation);
	GetWorld()->GetTimerManager().SetTimer(VictoryTimer, this, &UTQ_BattleLevelWidget::AfterVictory, VictoryAnimation->GetEndTime(), false);
}

void UTQ_BattleLevelWidget::AfterVictory()
{
	GetWorld()->GetTimerManager().ClearTimer(AnimationEnd);
	RemoveFromParent();

	CreateWidget(GetWorld(), TQBV_EventSystems.NarrationEvent.GoToNextMap)->AddToPlayerScreen(0);
}

ATQ_PlayerPawn* UTQ_BattleLevelWidget::GetCharacter()
{
	const auto Character = Cast<ATQ_PlayerPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	return Character;
} 

UTQ_InventoryComponent* UTQ_BattleLevelWidget::GetInventory()
{
	const auto Component = GetCharacter()->GetComponentByClass(UTQ_InventoryComponent::StaticClass());
	const auto InventoryComponent = Cast<UTQ_InventoryComponent>(Component);
	return InventoryComponent;
}

float UTQ_BattleLevelWidget::ProcessDamage(UTQ_InventoryComponent* Inventory)
{		
	float AdditionalDamage = 0.0f;
	float DmgFromInventory = 0.0f;
	IIP_InCharactersPocket = Inventory->GetIIP();
	if (IIP_InCharactersPocket.Num() != 0)
	{
		for (int32 PDmg_Index = 0; PDmg_Index <= 3; PDmg_Index++)
		{

			DmgFromInventory = Inventory->CompareIIP(IIP_InCharactersPocket[PDmg_Index], true); 

		}
		AdditionalDamage += DmgFromInventory;

	}
	UE_LOG(TQ_BattleLevelWidgetLog, Display, TEXT("AdditionalDamage: %f"), AdditionalDamage);

	return AdditionalDamage;
}

float UTQ_BattleLevelWidget::ProcessDefence(UTQ_InventoryComponent* Inventory)
{		
	float Additionaldefence = 0.0f;
	float DefFromInventory = 0.0f;
	IIP_InCharactersPocket = Inventory->GetIIP(); //new

	if ( IIP_InCharactersPocket.Num() != 0) 
	{
		for (int32 PDef_index = 0; PDef_index <= 3; PDef_index++)
		{
			DefFromInventory = Inventory->CompareIIP(IIP_InCharactersPocket[PDef_index], false);

		}
		Additionaldefence += DefFromInventory;

	}
	UE_LOG(TQ_BattleLevelWidgetLog, Display, TEXT("Additionaldefence: %f"), Additionaldefence);

	return Additionaldefence;
}

float UTQ_BattleLevelWidget::MakeDamage()
{
	float DamagModified = ProcessDamage(GetInventory());
	float DamagFromEffects = 0.0f;
	EffectsOnCharacter = GetCharacter()->GetEffects();
	int32 ELength = EffectsOnCharacter.Num() - 1;

	for (int32 MD_Index = 0; MD_Index <= ELength; MD_Index++)
	{
		if (EffectsToCheckAndDamagMonster.Find(EffectsOnCharacter[MD_Index]) != nullptr)
		{
			DamagFromEffects += *EffectsToCheckAndDamagMonster.Find(EffectsOnCharacter[MD_Index]);
		}
	}

	float FinalDamage = DamagFromEffects + DamagModified;

	return FinalDamage;
}

float UTQ_BattleLevelWidget::MakeDefence()
{
	float DefanceModified = ProcessDefence(GetInventory());
	float WeaknessFromEffects = 0.0f;
	EffectsOnCharacter = GetCharacter()->GetEffects();
	int32 ELength = EffectsOnCharacter.Num() - 1;

	for (int32 MDef_Index = 0; MDef_Index <= ELength; MDef_Index++)
	{
		if (EffectsToCheckAndDamagPlayer.Find(EffectsOnCharacter[MDef_Index]) != nullptr)
		{
			WeaknessFromEffects += *EffectsToCheckAndDamagPlayer.Find(EffectsOnCharacter[MDef_Index]);//
		}
	}

	float FinalDefence = WeaknessFromEffects + DefanceModified;
	return FinalDefence;
}

void UTQ_BattleLevelWidget::CkookDamage(float DamageModifire)
{
	float ModifireLuck = GetCharacter()->GetLuck();
	float DefencePercent = DamageModifire - (DamageModifire * ModifireLuck) - MakeDefence();
	GetCharacter()->ApplayDamageToSelf(DamageModifire - DefencePercent, TQBV_EventSystems.DamageTable.DamageType);
}

void UTQ_BattleLevelWidget::DamageForPlayer(float DamageModifire)
{
	CkookDamage(DamageModifire);
	PlayAnimationForward(AttackAnimation);
	GetWorld()->GetTimerManager().SetTimer(AnimationEnd, this, &UTQ_BattleLevelWidget::YourTurn, YourTurnAnimation->GetEndTime(), false);
	GetCharacter()->SetDeathWidget(TQBV_EventSystems.DeathScreens.DeathFromDamageEvents);
}

void UTQ_BattleLevelWidget::DamageForMonster() 
{
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	int32 StrengthModifire = GetCharacter()->GetStrength();
	int32 LuckModifire = GetCharacter()->GetLuck();
	float FinalDamage = 1 + MakeDamage() + (StrengthModifire * LuckModifire);
	MonsterHealth -= FinalDamage;

	if (MonsterHealth <= 0)
	{
			Victory();
		HUD->FromVictory();
	}
	
}

void UTQ_BattleLevelWidget::JustDamage()
{
	if (IsButtonsActive)
	{
		DamageForPlayer(TQBV_EventSystems.DamageTable.DefaultDamageToPlayer);
		ActionPoints += 2;
		RedrawActionPoints();
	}
}

void UTQ_BattleLevelWidget::MakeTurn()
{
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (TurnArrayState.Num() - 1 > -1)
	{
		ForbidClick(false);
		if (TurnArrayCount <= TurnArrayState.Num() - 1 && !ForbidFight)
		{
			PlayAnimationForward(TurnArrayState[TurnArrayCount].AnimationToPlay);

			HUD->UnsetAttackMessage();

			TurnArrayCount++;
			GetWorld()->GetTimerManager().SetTimer(DelayA, this, &UTQ_BattleLevelWidget::MakeTurn, 1.8f, true);
		}
		else
		{

				GetWorld()->GetTimerManager().ClearTimer(DelayA);
			TurnArrayState.Empty();
			TurnArrayCount = 0;
			HUD->UnsetAttackMessage();
			HUD->UI->DestroyAllContent();
			ForbidClick(true);

		}
	}

}

void UTQ_BattleLevelWidget::YourTurn()
{
	PlayAnimationForward(YourTurnAnimation);
	ForbidClick(true);
	GetWorld()->GetTimerManager().ClearTimer(AnimationEnd);
}

void UTQ_BattleLevelWidget::EnamyTurn()
{
	PlayAnimationForward(TurnEnamyAnimation);
	ForbidClick(true);
	GetWorld()->GetTimerManager().ClearTimer(AnimationEnd);
}

void UTQ_BattleLevelWidget::RedrawActionPoints()
{
	ActionPointsDisplay->SetText(FText::FromString(FString::FromInt(ActionPoints)));
}
