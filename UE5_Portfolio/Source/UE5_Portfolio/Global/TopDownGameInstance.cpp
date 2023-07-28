// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownGameInstance.h"
#include "../Monster/Data/NormalMonsterData.h"
#include "../Global/Data/UI_Data.h"

UTopDownGameInstance::UTopDownGameInstance()
{

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Monster/DataTable/DT_NormalMonster.DT_NormalMonster'");
		ConstructorHelpers::FObjectFinder<UDataTable> DT_NormalMonster(*DataPath);

		if (DT_NormalMonster.Succeeded())
		{
			NormalMonsterData = DT_NormalMonster.Object;
		}

	}
	 
	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_UI.DT_UI'");
		ConstructorHelpers::FObjectFinder<UDataTable> DT_UI(*DataPath);

		if (DT_UI.Succeeded())
		{
			UIData = DT_UI.Object;
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

FUI_Data* UTopDownGameInstance::GetUIData(FName _Name)
{
	if (UIData == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) GameInstance : NormalMonsterData is nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	FUI_Data* Table = UIData->FindRow<FUI_Data>(_Name, _Name.ToString());

	if (Table == nullptr)
	{
		return nullptr;
	}

	return Table;
}
