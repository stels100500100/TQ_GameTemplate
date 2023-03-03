// Fill out your copyright notice in the Description page of Project Settings.


#include "TQ_Components/TQ_WalkmanComponent.h"
#include <Kismet\GameplayStatics.h>
#include <Components/AudioComponent.h>
#include <Sound/SoundCue.h>

UTQ_WalkmanComponent::UTQ_WalkmanComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UTQ_WalkmanComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayNewMusic();

}


void UTQ_WalkmanComponent::PlayNewMusic()
{
	CurrentMusic = UGameplayStatics::SpawnSound2D(GetWorld(), PlayList[MusicIndexToPlay]);
}

void UTQ_WalkmanComponent::StopMusic()
{
	CurrentMusic->Stop();
	GetWorld()->GetTimerManager().ClearTimer(MusicHandle);
}

