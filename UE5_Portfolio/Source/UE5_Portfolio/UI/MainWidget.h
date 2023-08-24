// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public: 


	void TestWindowVisibilitySwitch()
	{
		int a = 0;
		TestWindowVisibility = TestWindowVisibility == ESlateVisibility::Hidden ?
			ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void InventoryWindowVisibilitySwitch()
	{
		int a = 0;
		InventoryyWindowVisibility = InventoryyWindowVisibility == ESlateVisibility::Hidden ?
			ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void ProgressBarVisibilitySwitch()
	{
		ProgressBarVisibility = ProgressBarVisibility == ESlateVisibility::Hidden?
			ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	FORCEINLINE void TurnOnProgressBar()
	{
		ProgressBarVisibility = ESlateVisibility::Visible;
	}

	FORCEINLINE void TurnOffProgressBar()
	{
		ProgressBarVisibility = ESlateVisibility::Hidden;
	}

	ESlateVisibility GetTestWindowVisibility()
	{
		return TestWindowVisibility;
	}

	ESlateVisibility GetInventoryyWindowVisibility()
	{
		return InventoryyWindowVisibility;
	}

	FORCEINLINE ESlateVisibility GetProgressBarVisibility()
	{
		return ProgressBarVisibility;
	}

private:


	UPROPERTY(Category = "TestWindowInfo", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility TestWindowVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "TestWindowInfo", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility InventoryyWindowVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "TestWindowInfo", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility ProgressBarVisibility = ESlateVisibility::Hidden;
};
