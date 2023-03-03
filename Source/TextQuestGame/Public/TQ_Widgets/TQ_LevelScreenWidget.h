// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TQ_Widgets/TQ_BaseLevelWidget.h"
#include <TQ_Utilitys/TQ_MovementStruct.h>
#include "TQ_LevelScreenWidget.generated.h"

class UButton;


UCLASS()
class TEXTQUESTGAME_API UTQ_LevelScreenWidget : public UTQ_BaseLevelWidget
{
	GENERATED_BODY()
private:

	virtual void NativeOnInitialized() override;

	virtual void ForbidClick(bool g) override;

	virtual void DestroyItem() override;

	UFUNCTION()
		void ObsticleHandling();
	UFUNCTION()
		void ObsticleStart();

	UFUNCTION(BlueprintCallable)
		void MoveForward();

	UFUNCTION(BlueprintCallable)
		void MoveBack();

	UFUNCTION(BlueprintCallable)
		void MoveRight();

	UFUNCTION(BlueprintCallable)
		void MoveLeft();

	UPROPERTY(meta = (BindWidget))
		UButton* GoForwardButton;

	UPROPERTY(meta = (BindWidget))
		UButton* GoBackwardButton;

	UPROPERTY(meta = (BindWidget))
		UButton* GoRightButton;

	UPROPERTY(meta = (BindWidget))
		UButton* GoLeftButton;

	UPROPERTY(EditAnywhere)
		FMovementStruct Movement;
};
