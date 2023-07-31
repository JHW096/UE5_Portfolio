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

	


	FSoftClassPath ClassPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_MainWidget.WBP_MainWidget_C'"));
	TSubclassOf<UUserWidget> MainWidgetClass = ClassPath.TryLoadClass<UUserWidget>();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	MainWidget = Cast<UMainWidget>(Widget);
	MainWidget->AddToViewport();

	{
		UUserWidget* Window = Cast<UUserWidget>(MainWidget->GetWidgetFromName(TEXT("Test_Widget")));
	}
}

void APortfolioHUD::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);
}
