// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "../State_Type/ItemType.h"		//for ItemType_Enum
#include "Engine/Texture.h"				//for Icon
#include "Engine/StaticMesh.h"			//for 3D obj_In_Map
#include "ItemData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	FItemData() { }
	~FItemData() { }


#pragma region Must_have_All_Items

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	ItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UTexture* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int StackMax = 1;

#pragma endregion


#pragma region Options_by_ItemsType
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int ATT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int Def;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int VALUE;

};
