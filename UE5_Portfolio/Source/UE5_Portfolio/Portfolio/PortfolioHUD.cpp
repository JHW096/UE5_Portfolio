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

	{

		FSoftClassPath ClassPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_MainWidget.WBP_MainWidget_C'"));
		TSubclassOf<UUserWidget> MainWidgetClass = ClassPath.TryLoadClass<UUserWidget>();

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
		MainWidget = Cast<UMainWidget>(Widget);
		MainWidget->AddToViewport();
	}
	

	{
		FSoftClassPath ClassPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Player_UI/WBP_TEST.WBP_TEST_C'"));
		TSubclassOf<UUserWidget> TestWidgetClass = ClassPath.TryLoadClass<UUserWidget>();

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), TestWidgetClass);
		TestWidget = Cast<UUserWidget>(Widget);
		TestWidget->AddToViewport();
	}
	
}

void APortfolioHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
