// InventoryManager.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryManager.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItemInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RequiredTitle;
};

UCLASS()
class CW01_API AInventoryManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AInventoryManager();
	
	void AddItemToBag(int32 ItemID);
	void PrintBag();
	void AcquireTitle(FName Title);
	void UseItem(int32 ItemID);

protected:
	virtual void BeginPlay() override;
	
	TArray<int32> Bag;
	TMap<int32, FInventoryItemInfo> ItemDatabase;
	TSet<FName> AcquiredTitles;
	
	void InitItemDatabase();
};
