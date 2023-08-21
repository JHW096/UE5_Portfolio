// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUserWidget.h"
#include "Components/TileView.h"
#include "../../Global/TopDownGameInstance.h"
#include "../Inventory/InvenItemData.h"
#include "../Inventory/ItemSlot.h"


void UInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InvenList = Cast<UTileView>(GetWidgetFromName(TEXT("InventoryTile")));

	UTopDownGameInstance* GameInst = GetWorld()->GetGameInstance<UTopDownGameInstance>();

	if (GameInst == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%s(%u) : GameInstance is nullptr"));
		return;
	}


	for (size_t i = 0; i < 20; i++)
	{
		int a = 0;
		UInvenItemData* Data = NewObject<UInvenItemData>();
		Data->m_ItemData = GameInst->GetItemData();
		InvenList->AddItem(Data);
	}

}

void UInventoryUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryUserWidget::AddInvenItem(UObject* _Data, UUserWidget* _Widget)
{
	UItemSlot* ItemSlotWidget = Cast<UItemSlot>(_Widget);

	UInvenItemData* InvenSlotData = Cast<UInvenItemData>(_Data);

	if (nullptr == ItemSlotWidget)
	{
		return;
	}

	ItemSlotWidget->SetItemData(InvenSlotData);


}

void UInventoryUserWidget::NewWidget(UUserWidget* _Widget)
{
}


