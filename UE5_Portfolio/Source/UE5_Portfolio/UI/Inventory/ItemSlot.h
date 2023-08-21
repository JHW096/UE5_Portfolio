// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Global/Data/ItemData.h"
#include "InvenItemData.h"
#include "../../Global/State_Type/ItemType.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:


	void SetItemData(UInvenItemData* _ItemData);

	void ItemSlotCheck();

public:

	FORCEINLINE UInvenItemData* GetInvenItemData() const
	{
		return m_InvenItemData;
	}


public:

	UPROPERTY(Category = "Visibility", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemIconVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Visibility", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemCountVisibility = ESlateVisibility::Hidden;

public:

	UPROPERTY(Category = "Image", EditAnywhere, BlueprintReadWrite)
	ItemType ItemSlotTypeValue = ItemType::NONE;

	UPROPERTY(Category = "Image", EditAnywhere, BlueprintReadWrite)
	UImage* ItemSlotBackGround = nullptr;

	UPROPERTY(Category = "Image", EditAnywhere, BlueprintReadWrite)
	UImage* ItemSlotIcon = nullptr;

	UPROPERTY(Category = "Image", EditAnywhere, BlueprintReadWrite)
	UTextBlock* ItemSlotCountText = nullptr;

	UPROPERTY(Category = "Image", EditAnywhere, BlueprintReadWrite)
	int ItemSlotCountValue = 0;

private:

	UInvenItemData* m_InvenItemData = nullptr;

};
