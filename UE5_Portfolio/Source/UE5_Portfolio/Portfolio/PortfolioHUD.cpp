// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioHUD.h"
#include "../Global/TopDownGameInstance.h"

APortfolioHUD::APortfolioHUD()
{
	
}

APortfolioHUD::~APortfolioHUD()
{
}

void APortfolioHUD::BeginPlay()
{
	Super::BeginPlay();

	UTopDownGameInstance* GameInst = Cast<UTopDownGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : GameInstance == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	MainWidget = GameInst->GetUIData(MainWidgetName);
	

}

void APortfolioHUD::Tick(float _Delta)
{
	Super::Tick(_Delta);


}
