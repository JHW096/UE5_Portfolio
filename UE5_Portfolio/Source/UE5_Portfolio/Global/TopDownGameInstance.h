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

	struct FNormalMonsterData* GetNormalMonsterData(FName Name);

	struct FTest2* GetTestData(FName Name);

public:

	UPROPERTY()
	UDataTable* DataTable;

	UPROPERTY()
	UDataTable* NormalMonsterData;

	UPROPERTY()
	UDataTable* UIData;

};
