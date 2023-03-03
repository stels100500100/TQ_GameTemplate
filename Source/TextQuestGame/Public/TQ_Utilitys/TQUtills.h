#pragma once
#include <TQUtills.generated.h>

UENUM(BlueprintType)
enum class EStatusAutoCheck : uint8
{
	Luck = 0,
	Strength,
	Intellegents
};

DECLARE_MULTICAST_DELEGATE_OneParam(FCheckStatusAutoSignature, FString);
DECLARE_MULTICAST_DELEGATE_OneParam(FCheckEffectAutoSignature, FString);
DECLARE_MULTICAST_DELEGATE(FSpeakerRequest);

UENUM(BlueprintType)
enum class EEventResponseManager : uint8
{
	Damage = 0,
	Speach,
	InventoryHandling,
	AddEffect,
	GoToNextMap,
	HiddenObjectHandling,
	Heal,
	Nothing
};

UENUM(BlueprintType)
enum class EHiddenObjectHandling : uint8
{
	Nothing = 0,
	Hide,
	HidePermanently,
	Revial
};

USTRUCT(BlueprintType)
struct FImageSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
		UTexture2D* Images;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool HasEvent = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "HasEvent"))
		EEventResponseManager WhatToDo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		EHiddenObjectHandling WhatHiddenObjectDo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "HasEvent"))
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "HasEvent"))
		TSubclassOf<UUserWidget> DeathRes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "HasEvent"))
		FString Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "HasEvent"))
		FString Speech;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "HasEvent"))
		TSubclassOf<UUserWidget> MapToGoFromImageSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "HasEvent"))
		int32 Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "HasEvent"))
		bool bWantDerectioninfluence = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "WantDerectioninfluence"))
		bool ForwardMove = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "WantDerectioninfluence"))
		bool BackMove = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "WantDerectioninfluence"))
		bool LeftMove = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (EditCondition = "WantDerectioninfluence"))
		bool RightMove = false;
};

USTRUCT(BlueprintType)
struct FSaveMapState
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapState")
		bool ShowTextMessageOnStart = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapState")
		bool IsLevelAlreadyEntered = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapState")
		bool IsHiddenObjectExist = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapState")
		bool IsObsticleVisible = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapState")
		bool IsRandomEventNeeded = true;

};