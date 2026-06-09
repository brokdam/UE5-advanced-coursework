// InventoryManager.cpp

#include "InventoryManager.h"

AInventoryManager::AInventoryManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInventoryManager::AddItemToBag(int32 ItemID)
{
	if (ItemDatabase.Contains(ItemID))
	{
		Bag.Add(ItemID);
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
			FString::Printf(TEXT("가방에 담음: ID %d"), ItemID));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			FString::Printf(TEXT("그런 아이템 없음: ID %d"), ItemID));
	}
}

void AInventoryManager::PrintBag()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,
		FString::Printf(TEXT("가방 (%d개)"), Bag.Num()));
	
	for (int32 ItemID : Bag)
	{
		FInventoryItemInfo* Info = ItemDatabase.Find(ItemID);

		if (Info)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
				FString::Printf(TEXT("[%d] %s / 가격 %d / 필요칭호 %s"),
					ItemID,
					*Info->ItemName,
					Info->Price,
					*Info->RequiredTitle.ToString()));
		}
	}
}

void AInventoryManager::BeginPlay()
{
	Super::BeginPlay();
	
	InitItemDatabase();
}

void AInventoryManager::InitItemDatabase()
{
	ItemDatabase.Add(1001, FInventoryItemInfo{ TEXT("Wooden Sword"), 50,  NAME_None });
	ItemDatabase.Add(1002, FInventoryItemInfo{ TEXT("Iron Sword"),   150, FName("Warrior") });
	ItemDatabase.Add(1003, FInventoryItemInfo{ TEXT("Magic Staff"),  300, FName("Mage") });
	ItemDatabase.Add(1004, FInventoryItemInfo{ TEXT("Health Potion"),30,  NAME_None });

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan,
		FString::Printf(TEXT("DB 등록 완료: 아이템 %d종"), ItemDatabase.Num()));
}


