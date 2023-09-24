// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBattleItemBase.h"

void APlayerControllerBattleItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerControllerBattleItemBase::PlayerTick(float _DeltaSeconds)
{
	Super::PlayerTick(_DeltaSeconds);
}

void APlayerControllerBattleItemBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	AddInputAction(FName("FristBattleItemKey"), FristBattleItemKey);
	AddInputAction(FName("SecondBattleItemKey"), SecondBattleItemKey);
	AddInputAction(FName("ThirdBattleItemKey"), ThirdBattleItemKey);
	AddInputAction(FName("ForthBattleItemKey"), ForthBattleItemKey);

	{
		EnhancedInputComponent->BindAction(
			FristBattleItemKey, ETriggerEvent::Started, this, &APlayerControllerBattleItemBase::OnFristStart
		);
	}
}

void APlayerControllerBattleItemBase::OnFristStart()
{
	//TODO_UI & Character 
}


