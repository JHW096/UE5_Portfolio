// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"
#include "InventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void AddInvenItem(UObject* _Data, UUserWidget* _Widget);

	UFUNCTION(BlueprintCallable)
	void NewWidget(UUserWidget* _Widget);

protected:

	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	UPROPERTY(Category = "InvenList", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTileView* InvenList = nullptr;
};
