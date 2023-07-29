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


	ESlateVisibility GetTestWindowVisibility()
	{
		return TestWindowVisibility;
	}

private:


	UPROPERTY(Category = "TestWindowInfo", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility TestWindowVisibility = ESlateVisibility::Hidden;

};
