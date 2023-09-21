// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerUI.h"
#include "../../UI/Skill/PlayerSkillTileViewWidget.h"
#include "../../UI/Skill/PlayerSkillWidget.h"
#include "Blueprint/UserWidget.h"
#include "../../Portfolio/PortfolioHUD.h"
#include "Components/ProgressBar.h"

void AControllerUI::BeginPlay()
{
	Super::BeginPlay();
}

void AControllerUI::SetupInputComponent()
{
	int b = 0;
	Super::SetupInputComponent();
	if (EnhancedInputComponent)
	{
		int a = 0;
		//RKey
		{
			EnhancedInputComponent->BindAction(
				InputRKeyAction, ETriggerEvent::Started, this, &AControllerUI::RKeyPressedUI
			);
		}
	}

	
}

void AControllerUI::PlayerTick(float _DeltaSeconds)
{
	Super::PlayerTick(_DeltaSeconds);
}

void AControllerUI::RKeyPressedUI()
{
	int a = 0;
	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();
	if (HUD == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) ControllerUI_HUD == nullptr"), __FUNCTION__, __LINE__);
		return;
	}
	
	UUserWidget* MainWidget = HUD->GetMainWidget();
	if (MainWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) MainWidget == nullptr"), __FUNCTION__, __LINE__);
		return;
	}
	
	UPlayerSkillTileViewWidget* PlayerSkillTileViewWidget = Cast<UPlayerSkillTileViewWidget>(MainWidget->GetWidgetFromName(TEXT("WBP_PlayerSkillTileViewWidget")));
	if (PlayerSkillTileViewWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) PlayerSkillTileViewWidget == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	UPlayerSkillWidget* PlayerSkillWidget = PlayerSkillTileViewWidget->GetPlayerSkillWidgetFromTileView(0);

	UProgressBar* ProgressBar = PlayerSkillWidget->GetProgressBar();

	
	float TempRatio = (float)PlayerSkillWidget->GetMaxCoolTime() / (float)PlayerSkillWidget->GetMaxCoolTime();

	ProgressBar->SetPercent(TempRatio);
	
}
