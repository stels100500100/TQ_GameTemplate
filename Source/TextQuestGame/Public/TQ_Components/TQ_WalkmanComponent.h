// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
#include <Components/AudioComponent.h>
#include "TQ_WalkmanComponent.generated.h"

class USoundCue;
class UAudioComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEXTQUESTGAME_API UTQ_WalkmanComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTQ_WalkmanComponent();

	int32 SetMusicIndexToPlay(int32 index) { return MusicIndexToPlay = index; };

	UAudioComponent* CurrentMusic;

	void PlayNewMusic();
	void StopMusic();

	UPROPERTY(EditAnywhere)
		TArray<USoundCue*> PlayList;
		int32 MusicIndexToPlay = 0;
		FTimerHandle MusicHandle;

protected:
	virtual void BeginPlay() override;

};
