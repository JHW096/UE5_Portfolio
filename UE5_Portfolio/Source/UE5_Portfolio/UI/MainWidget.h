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

	void SetStatusWindowOnOffSwitch()
	{
		StatusWindowOnOff = StatusWindowOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	ESlateVisibility GetStatusWindowOnOff()
	{
		return StatusWindowOnOff;
	}


private: 

	UPROPERTY(Category = "SubUIWidget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility StatusWindowOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "SubUIWidget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility TestWindow = ESlateVisibility::Hidden;

};
