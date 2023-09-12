// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PlayerSkillData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FPlayerSkillData : public FTableRowBase
{
	GENERATED_BODY()

	FPlayerSkillData() { }
	~FPlayerSkillData() { }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillCoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UTexture* SkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UTextBlock* SkillCoolTimeTextBlock;
	
	
	//Relative Combat

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillPower;

	
};

