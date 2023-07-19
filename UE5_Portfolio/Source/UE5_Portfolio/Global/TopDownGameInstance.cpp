// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownGameInstance.h"
#include "../Monster/Data/NormalMonsterData.h"

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
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Monster/DataTable/DT_NormalMonster.DT_NormalMonster'");
		ConstructorHelpers::FObjectFinder<UDataTable> DT_NormalMonster(*DataPath);

		if (DT_NormalMonster.Succeeded())
		{
			NormalMonsterData = DT_NormalMonster.Object;
		}

	}
}

UTopDownGameInstance::~UTopDownGameInstance()
{
}

FNormalMonsterData* UTopDownGameInstance::GetNormalMonsterData(FName Name)
{
	if (NormalMonsterData == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) GameInstance : NormalMonsterData is nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	FNormalMonsterData* Table = NormalMonsterData->FindRow<FNormalMonsterData>(Name, Name.ToString());

	if (Table == nullptr)
	{
		return nullptr;
	}

	return Table;
}
