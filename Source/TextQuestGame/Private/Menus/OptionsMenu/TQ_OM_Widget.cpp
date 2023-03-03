// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/OptionsMenu/TQ_OM_Widget.h"
#include "Components/Slider.h"
#include "Sound/SoundClass.h"
#include "Components/Button.h"

void UTQ_OM_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (VolumeSlider) VolumeSlider->OnValueChanged.AddDynamic(this, &UTQ_OM_Widget::ChangeSoundCalssVolume);
	if (CloseButton) CloseButton->OnClicked.AddDynamic(this, &UTQ_OM_Widget::RemoveFromParent);
}


void UTQ_OM_Widget::ChangeSoundCalssVolume(float Volume)
{

	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.01f, 1.0f);
}

