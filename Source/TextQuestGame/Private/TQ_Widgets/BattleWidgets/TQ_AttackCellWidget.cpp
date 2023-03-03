// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/BattleWidgets/TQ_AttackCellWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include <Player/TQ_PlayerHUD.h>

void UTQ_AttackCellWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Cancel)
	{
		Cancel->OnClicked.AddDynamic(this, &UTQ_AttackCellWidget::DestroyBattleCell);
	}

	if (!ScoreTB)
	{
		return;
	}

	if (!ActionNameTB)
	{
		return;
	}

	if (!TextBX)
	{
		return;
	}

	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	HUD->ACAS.AddUObject(this, &UTQ_AttackCellWidget::EndAnimation);
	HUD->ACIS.AddUObject(this, &UTQ_AttackCellWidget::SetBaseDeleteIndex);

}

void UTQ_AttackCellWidget::SetBaseDeleteIndex(int32 DeleteIndexSetter)
{
	if (Seted)
	{
		BaseDeleteIndex = DeleteIndexSetter;
		Seted = false;
	}
	FString g = FString::FromInt(BaseDeleteIndex);
	TextBX->SetText(FText::FromString(g));
}

void UTQ_AttackCellWidget::DestroyBattleCell()
{
	const auto HUD = Cast<ATQ_PlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	HUD->ACS.Broadcast();

	RemoveFromParent();
}

void UTQ_AttackCellWidget::SetBattleStatsVisually()
{
	ScoreTB->SetText(FText::FromString(FString::FromInt(Score)));
	ActionNameTB->SetText(ActionName);
}

void UTQ_AttackCellWidget::EndAnimation(int32 DeleteIndex)
{

	if (BaseDeleteIndex == DeleteIndex)
	{
		PlayAnimationForward(OnDestroy);
	}
}

