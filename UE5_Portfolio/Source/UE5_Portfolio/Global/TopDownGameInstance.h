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

	float GetValue();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowAccessPrivate = "true"))
	UDataTable* DataTable = nullptr;

	

};
