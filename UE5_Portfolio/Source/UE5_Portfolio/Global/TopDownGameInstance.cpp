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
}

UTopDownGameInstance::~UTopDownGameInstance()
{
}
