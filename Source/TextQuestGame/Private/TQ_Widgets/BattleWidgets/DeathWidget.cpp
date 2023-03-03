// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Widgets/BattleWidgets/DeathWidget.h"
#include "Sound/SoundCue.h"
#include <Kismet\GameplayStatics.h>

void UDeathWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	PlayAnimationForward(AppearAnim);
	UGameplayStatics::SpawnSound2D(GetWorld(), DeathSound);
	
}