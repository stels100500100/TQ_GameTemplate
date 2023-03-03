#pragma once
#include <TQ_Widgets/TQ_BaseLevelWidget.h>
#include <TQ_MovementStruct.generated.h>

class UTQ_BaseLevelWidget;

USTRUCT(BlueprintType)
struct FMovementStruct
{
	GENERATED_USTRUCT_BODY()
		//Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay-Movement")
		TSubclassOf<UUserWidget> ForwardScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay-Movement")
		TSubclassOf<UUserWidget> BackwardScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay-Movement")
		TSubclassOf<UUserWidget> LeftScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay-Movement")
		TSubclassOf<UUserWidget> RightScreen;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obsticle", meta = (Tooltip = "If true, Obsticle cuts way to the left."), meta = (EditCondition = "!TreatAsObsticle"))
		bool ObsticleLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obsticle", meta = (Tooltip = "If true, Obsticle cuts way to the right."), meta = (EditCondition = "!TreatAsObsticle"))
		bool ObsticleRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obsticle", meta = (Tooltip = "If true, Obsticle cuts way to the forward."), meta = (EditCondition = "!TreatAsObsticle"))
		bool ObsticleForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obsticle", meta = (Tooltip = "If true, Obsticle cuts way to the backward."), meta = (EditCondition = "!TreatAsObsticle"))
		bool ObsticleBackward;
};