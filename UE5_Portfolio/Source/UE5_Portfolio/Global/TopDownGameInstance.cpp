// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownGameInstance.h"

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
