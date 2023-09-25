// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture.h"				//for Icon
#include "GreatSwordSkillData.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FGreatSwordSkillData : public FTableRowBase
{
	GENERATED_BODY()

public:

	FGreatSwordSkillData() {  }
	~FGreatSwordSkillData() {  }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SkillCoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UTexture2D* SkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillPower;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MpRequired;
};
