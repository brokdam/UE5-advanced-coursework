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

void AInventoryManager::AcquireTitle(FName Title)
{
	AcquiredTitles.Add(Title);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta,
		FString::Printf(TEXT("칭호 획득: %s"), *Title.ToString()));
}

void AInventoryManager::UseItem(int32 ItemID)
{
	if (!Bag.Contains(ItemID))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			FString::Printf(TEXT("가방에 없는 아이템: ID %d"), ItemID));
		return;
	}
	
	FInventoryItemInfo* Info = ItemDatabase.Find(ItemID);
	if (!Info)
	{
		return;
	}
	
	bool bNoTitleNeeded = (Info->RequiredTitle == NAME_None);
	bool bHasTitle      = AcquiredTitles.Contains(Info->RequiredTitle);
	
	if (bNoTitleNeeded || bHasTitle)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			FString::Printf(TEXT("%s 사용 성공!"), *Info->ItemName));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			FString::Printf(TEXT("%s 사용 불가 : '%s' 칭호가 필요합니다"),
				*Info->ItemName, *Info->RequiredTitle.ToString()));
	}
}

void AInventoryManager::BeginPlay()
{
	Super::BeginPlay();
	
	InitItemDatabase();
	
	AddItemToBag(1001);  
	AddItemToBag(1003);  

	UseItem(1001);      
	UseItem(1003);      

	AcquireTitle(FName("Mage")); 

	UseItem(1003); 
}

void AInventoryManager::InitItemDatabase()
{
	ItemDatabase.Add(1001, FInventoryItemInfo{ TEXT("Wooden Sword"), 50,  NAME_None });
	ItemDatabase.Add(1002, FInventoryItemInfo{ TEXT("Iron Sword"),   150, FName("Warrior") });
	ItemDatabase.Add(1003, FInventoryItemInfo{ TEXT("Magic Staff"),  300, FName("Mage") });
	ItemDatabase.Add(1004, FInventoryItemInfo{ TEXT("Health Potion"),30,  NAME_None });

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
		FString::Printf(TEXT("DB 등록 완료: 아이템 %d종"), ItemDatabase.Num()));
}


