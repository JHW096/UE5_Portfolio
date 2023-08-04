// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemIconImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	ItemCountBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));

}

void UItemSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UItemSlot::SetItemData(const FItemData* _ItemData)
{
	ItemData = _ItemData;

	if (nullptr == ItemData)
	{
		ItemIconVisibility = ESlateVisibility::Hidden;
		return;
	}

	if (nullptr != ItemData)
	{
		ItemIconVisibility = ESlateVisibility::Visible;
		ItemIconImage->SetBrushFromTexture(Cast<UTexture2D>(_ItemData->Icon));

		if (1 < ItemData->StackMax)
		{
			ItemCountVisibility = ESlateVisibility::Visible;
			ItemCountValue = 1;
		}
		else
		{
			ItemCountVisibility = ESlateVisibility::Hidden;
		}
	}

}
