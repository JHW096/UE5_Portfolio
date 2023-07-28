// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../UI/MainWidget.h"
#include "PortfolioHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API APortfolioHUD : public AHUD
{
	GENERATED_BODY()

	APortfolioHUD();
	~APortfolioHUD();

public:

	UUserWidget* GetMainWidget()
	{
		return MainWidget;
	}

protected:

	void BeginPlay() override;
	void Tick(float _Delta) override;


private: 

	UUserWidget* MainWidget = nullptr;

	const struct FUI_Data* CurUIData;
	
	UPROPERTY(Category = "DataName", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName MainWidgetName = "MainWidget";
};
