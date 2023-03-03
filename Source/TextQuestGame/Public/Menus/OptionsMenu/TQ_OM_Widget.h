// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TQ_OM_Widget.generated.h"

class USlider;
class USoundClass;
class UButton;

UCLASS()
class TEXTQUESTGAME_API UTQ_OM_Widget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
		USlider* VolumeSlider;

	UPROPERTY(meta = (BindWidget))
		UButton* CloseButton;

	UPROPERTY(EditAnywhere)
		USoundClass* SoundClass;

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
		void ChangeSoundCalssVolume(float Volume);
};
