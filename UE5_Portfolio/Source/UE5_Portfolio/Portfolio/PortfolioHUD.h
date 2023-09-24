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


public:
	APortfolioHUD();
	~APortfolioHUD();

	UMainWidget* GetMainWidget()
	{
		return MainWidget;
	}

protected:

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;


private:

	const struct FTest2* UIDataTable;

	UMainWidget* MainWidget = nullptr;

	UUserWidget* TestWidget = nullptr;

};
