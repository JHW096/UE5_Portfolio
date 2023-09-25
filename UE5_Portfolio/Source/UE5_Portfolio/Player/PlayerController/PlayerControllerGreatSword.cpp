// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerGreatSword.h"
#include "../Character/GreatSwordCharacter.h"

APlayerControllerGreatSword::APlayerControllerGreatSword()
{
}

void APlayerControllerGreatSword::BeginPlay()
{
	Super::BeginPlay();

	m_Player = Cast<AGreatSwordCharacter>(GetPawn());
	if (m_Player == nullptr)
	{
		return;
	}
}

void APlayerControllerGreatSword::PlayerTick(float _DeltaSeconds)
{
	Super::PlayerTick(_DeltaSeconds);
}

void APlayerControllerGreatSword::SetupInputComponent()
{
	Super::SetupInputComponent();

	AddInputAction(FName("InputCAction"), InputCAction);
	AddInputAction(FName("InputQAction"), InputQAction);
	AddInputAction(FName("InputWAction"), InputWAction);
	AddInputAction(FName("InputEAction"), InputEAction);
	AddInputAction(FName("InputRAction"), InputRAction);


	//Input C Key Binding
	{
		EnhancedInputComponent->BindAction(
			InputCAction, ETriggerEvent::Started, this, &APlayerControllerGreatSword::InputCKeyStart
		);

	}
}

void APlayerControllerGreatSword::InputCKeyStart()
{
	

	m_Player->SetPlayerAnimState(GreatSwordAnimState::CKey);
}

void APlayerControllerGreatSword::InputQKeyStart()
{

	m_Player->SetPlayerAnimState(GreatSwordAnimState::QKey);
}

void APlayerControllerGreatSword::InputWKeyStart()
{

	m_Player->SetPlayerAnimState(GreatSwordAnimState::WKey);
}

void APlayerControllerGreatSword::InputEKeyStart()
{

	m_Player->SetPlayerAnimState(GreatSwordAnimState::EKey);
}

void APlayerControllerGreatSword::InputRKeyStart()
{

	m_Player->SetPlayerAnimState(GreatSwordAnimState::RKey);
}
