// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioGameMode.h"
#include "PortfolioPlayerController.h"
#include "MainPlayer.h"
#include "PortfolioHUD.h"
#include "UObject/ConstructorHelpers.h"



APortfolioGameMode::APortfolioGameMode()
{
	PlayerControllerClass = AMainPlayer::StaticClass();
	HUDClass = AHUD::StaticClass();


	static ConstructorHelpers::FClassFinder<APawn> BP_MainPlayer(
		TEXT("/Script/Engine.Blueprint'/Game/GameMode/BP_MainPlayer.BP_MainPlayer_C'")
	);
	if (BP_MainPlayer.Succeeded())
	{
		DefaultPawnClass = BP_MainPlayer.Class;
	}


	static ConstructorHelpers::FClassFinder<APlayerController> BP_PlayerController(
		TEXT("/Script/Engine.Blueprint'/Game/GameMode/BP_PlayerController.BP_PlayerController_C'")
	);
	if (BP_PlayerController.Succeeded())
	{
		PlayerControllerClass = BP_PlayerController.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> BP_HUD(
		TEXT("/Script/Engine.Blueprint'/Game/GameMode/BP_HUD.BP_HUD_C'")
	);
	if (BP_HUD.Succeeded())
	{
		HUDClass = BP_HUD.Class;
	}

	

}
