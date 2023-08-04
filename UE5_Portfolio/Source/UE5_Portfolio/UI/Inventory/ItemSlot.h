// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Global/Data/ItemData.h"
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

	void SetItemData(const FItemData* _ItemData);

public:

	UPROPERTY(Category = "Visibility", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemIconVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Visibility", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemCountVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Image", EditAnywhere, BlueprintReadWrite)
	UImage* ItemIconImage = nullptr;

	UPROPERTY(Category = "Text", EditAnywhere, BlueprintReadWrite)
	UTextBlock* ItemCountBlock = nullptr;

	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
	int ItemCountValue = 1;

private:

	const FItemData* ItemData = nullptr;

};
