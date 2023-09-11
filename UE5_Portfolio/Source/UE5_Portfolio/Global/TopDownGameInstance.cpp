// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownGameInstance.h"
#include "../Monster/Data/NormalMonsterData.h"
#include "../Monster/Data/MonsterData.h"
#include "Data/Test2.h"
#include "Data/ItemData.h"
#include "Data/SubClassData.h"
#include "../Player/Data/PlayerStatData.h"

FRandomStream UTopDownGameInstance::MainRandom;

UTopDownGameInstance::UTopDownGameInstance()
{

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_PlayerStat.DT_PlayerStat'");
		ConstructorHelpers::FObjectFinder<UDataTable> DT_PlayerStat(*DataPath);

		if (DT_PlayerStat.Succeeded()) 
		{
			PlayerStatData = DT_PlayerStat.Object;
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
		
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_SubClass.DT_SubClass'");
		ConstructorHelpers::FObjectFinder<UDataTable> DT_SubClass(*DataPath);

		if (DT_SubClass.Succeeded())
		{
			SubClassData = DT_SubClass.Object;
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

	MainRandom.GenerateNewSeed();
}

UTopDownGameInstance::~UTopDownGameInstance()
{
}

TSubclassOf<UObject> UTopDownGameInstance::GetSubClass(FName _Name)
{
	if (SubClassData == nullptr)
	{
		return nullptr;
	}

	FSubClassData* FindTable = SubClassData->FindRow<FSubClassData>(_Name, _Name.ToString());

	if (FindTable == nullptr)
	{
		return nullptr;
	}

	return FindTable->Object;
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

FPlayerStatData* UTopDownGameInstance::GetPlayerStatData(FName Name)
{
	if (PlayerStatData == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) GameInstance : PlayerStatData == nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	FPlayerStatData* Table = PlayerStatData->FindRow<FPlayerStatData>(Name, Name.ToString());


	if (Table == nullptr) {
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

