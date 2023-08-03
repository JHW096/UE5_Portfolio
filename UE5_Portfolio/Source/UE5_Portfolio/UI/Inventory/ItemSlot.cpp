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
}
