// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "TopDownGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UTopDownGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UTopDownGameInstance();
	~UTopDownGameInstance();


public: 

	TSubclassOf<UObject> GetSubClass(FName _Name);

	struct FMonsterData* GetNormalMonsterData(FName Name);

	struct FPlayerStatData* GetPlayerStatData(FName Name);

	const struct FItemData* GetItemData();

public:

	UPROPERTY()
	UDataTable* SubClassData;

	UPROPERTY()
	UDataTable* DataTable;

	UPROPERTY()
	UDataTable* NormalMonsterData;

	UPROPERTY()
	UDataTable* UIData;

	UPROPERTY()
	UDataTable* ItemDatas;

	UPROPERTY()
	UDataTable* PlayerStatData;


	TArray<const struct FItemData*> ItemDataRandoms;

	static FRandomStream MainRandom;

};
