#pragma once
#include <TQ_InventoryStruct.generated.h>

DECLARE_MULTICAST_DELEGATE(FInventoryUpdate);


USTRUCT(BlueprintType)
struct FInventoryItemStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame-Item")
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame-Item")
		FText Discription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TQGame-Item")
		FString Effect;
};