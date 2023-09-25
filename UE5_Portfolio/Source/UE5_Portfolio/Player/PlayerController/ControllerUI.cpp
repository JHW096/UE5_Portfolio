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


}
