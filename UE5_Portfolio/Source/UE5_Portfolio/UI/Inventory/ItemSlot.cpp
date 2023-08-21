// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	/*
	
	*/
	/*ItemIconImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	ItemCountBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));*/

	ItemSlotIcon = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	ItemSlotCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	
	m_InvenItemData = NewObject<UInvenItemData>();
}

void UItemSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UItemSlot::SetItemData(UInvenItemData* _ItemData)
{
	m_InvenItemData = _ItemData;

	if (nullptr == m_InvenItemData)
	{
		ItemIconVisibility = ESlateVisibility::Hidden;
		return;
	}

	if (nullptr != m_InvenItemData)
	{
		ItemIconVisibility = ESlateVisibility::Visible;
		//ItemIconImage->SetBrushFromTexture(Cast<UTexture2D>(_ItemData->Icon));

		if (1 < m_InvenItemData->Count)
		{
			ItemCountVisibility = ESlateVisibility::Visible;
			//ItemCountValue = 1;
		}
		else
		{
			ItemCountVisibility = ESlateVisibility::Hidden;
		}
	}

}

void UItemSlot::ItemSlotCheck()
{
	if (m_InvenItemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s(%u) class InvenSlot::m_InvenItemData == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	if (m_InvenItemData->m_ItemData == nullptr)
	{
		ItemIconVisibility = ESlateVisibility::Hidden;
		ItemCountVisibility = ESlateVisibility::Hidden;
		return;
	}
	
	if(m_InvenItemData->m_ItemData != nullptr)
	{
		ItemIconVisibility = ESlateVisibility::Visible;
		ItemSlotIcon->SetBrushFromTexture(Cast<UTexture2D>(m_InvenItemData->m_ItemData->Icon));
		ItemSlotCountValue = m_InvenItemData->Count;

		if (m_InvenItemData->m_ItemData->CountMax > 1)
		{
			ItemCountVisibility = ESlateVisibility::Visible;
		}
		else
		{
			ItemCountVisibility = ESlateVisibility::Hidden;
		}
		
	}


}
