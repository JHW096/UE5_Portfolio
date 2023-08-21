// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownGameInstance.h"
#include "../Monster/Data/NormalMonsterData.h"
#include "../Monster/Data/MonsterData.h"
#include "Data/Test2.h"
#include "Data/ItemData.h"

FRandomStream UTopDownGameInstance::MainRandom;

UTopDownGameInstance::UTopDownGameInstance()
{
	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_Test.DT_Test'");
		ConstructorHelpers::FObjectFinder<UDataTable> DATA_TABLE(*DataPath);
		if (DATA_TABLE.Succeeded())
		{
			DataTable = DATA_TABLE.Object;
		}
	}

	{
		/*FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Monster/DataTable/DT_NormalMonster.DT_NormalMonster'");
		ConstructorHelpers::FObjectFinder<UDataTable> DT_NormalMonster(*DataPath);

		if (DT_NormalMonster.Succeeded())
		{
			NormalMonsterData = DT_NormalMonster.Object;
		}*/

	}

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_Test2.DT_Test2'");
		ConstructorHelpers::FObjectFinder<UDataTable> DT_UITest(*DataPath);

		if (DT_UITest.Succeeded())
		{
			UIData = DT_UITest.Object;
		}
	}
	
	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_Monster.DT_Monster'");
		ConstructorHelpers::FObjectFinder<UDataTable> DT_NormalMonster(*DataPath);

		if (DT_NormalMonster.Succeeded())
		{
			NormalMonsterData = DT_NormalMonster.Object;
		}
	}

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_ItemData.DT_ItemData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DT_Item(*DataPath);

		if (DT_Item.Succeeded())
		{
			ItemDatas = DT_Item.Object;

			TArray<FName> ArrayName = ItemDatas->GetRowNames();

			for (size_t i = 0; i < ArrayName.Num(); i++)
			{
				FItemData* m_ItemData = ItemDatas->FindRow<FItemData>(ArrayName[i], ArrayName[i].ToString());
				ItemDataRandoms.Add(m_ItemData);
			}
		}
	}
}

UTopDownGameInstance::~UTopDownGameInstance()
{
}

FMonsterData* UTopDownGameInstance::GetNormalMonsterData(FName Name)
{
	if (NormalMonsterData == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) GameInstance : NormalMonsterData is nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	FMonsterData* Table = NormalMonsterData->FindRow<FMonsterData>(Name, Name.ToString());

	if (Table == nullptr)
	{
		return nullptr;
	}

	return Table;
}

FTest2* UTopDownGameInstance::GetTestData(FName Name)
{
	if (UIData == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) GameInstance : UIData is nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	FTest2* Table = UIData->FindRow<FTest2>(Name, Name.ToString());

	if (Table == nullptr)
	{
		return nullptr;
	}

	return Table;
}

const FItemData* UTopDownGameInstance::GetItemData()
{
	if (true == ItemDataRandoms.IsEmpty())
	{
		return nullptr;
	}

	return ItemDataRandoms[UTopDownGameInstance::MainRandom.RandRange(0, ItemDataRandoms.Num() - 1)];
}

