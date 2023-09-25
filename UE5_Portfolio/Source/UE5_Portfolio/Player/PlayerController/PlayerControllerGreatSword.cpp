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


	//Input Q Key Binding
	{
		EnhancedInputComponent->BindAction(
			InputQAction, ETriggerEvent::Started, this, &APlayerControllerGreatSword::InputQKeyStart
		);
	}


	//Input W Key Binding
	{
		EnhancedInputComponent->BindAction(
			InputWAction, ETriggerEvent::Started, this, &APlayerControllerGreatSword::InputWKeyStart
		);
	}

	//Input E Key Binding
	{
		EnhancedInputComponent->BindAction(
			InputEAction, ETriggerEvent::Started, this, &APlayerControllerGreatSword::InputEKeyStart
		);
	}


	//Input R Key Binding
	{
		EnhancedInputComponent->BindAction(
			InputRAction, ETriggerEvent::Started, this, &APlayerControllerGreatSword::InputRKeyStart
		);

		/*EnhancedInputComponent->BindAction(
			InputRAction, ETriggerEvent::Triggered, this, &APlayerControllerGreatSword::InputRKeyStart
		);*/
	}

}

void APlayerControllerGreatSword::InputCKeyStart()
{
	if (HitSucceeded())
	{
		FVector Dir = GetCursorHitResult().Location - GetPawn()->GetActorLocation();
		Dir = Dir.GetSafeNormal();
		FRotator Rot = Dir.Rotation();
		Rot.Pitch = 0.0f;
		GetPawn()->SetActorRotation(Rot);
	}

	m_Player->SetPlayerAnimState(GreatSwordAnimState::CKey);
}

void APlayerControllerGreatSword::InputQKeyStart()
{
	if (HitSucceeded())
	{
		FVector Dir = GetCursorHitResult().Location - GetPawn()->GetActorLocation();
		Dir = Dir.GetSafeNormal();
		FRotator Rot = Dir.Rotation();
		Rot.Pitch = 0.0f;
		GetPawn()->SetActorRotation(Rot);
	}

	m_Player->SetPlayerAnimState(GreatSwordAnimState::QKey);
}

void APlayerControllerGreatSword::InputWKeyStart()
{

	m_Player->SetPlayerAnimState(GreatSwordAnimState::WKey);
}

void APlayerControllerGreatSword::InputEKeyStart()
{
	StopMovement();

	if (HitSucceeded())
	{
		FVector Dir = GetCursorHitResult().Location - GetPawn()->GetActorLocation();
		Dir = Dir.GetSafeNormal();
		FRotator Rot = Dir.Rotation();
		Rot.Pitch = 0.0f;
		GetPawn()->SetActorRotation(Rot);
		
	}


	m_Player->SetPlayerAnimState(GreatSwordAnimState::EKey);
}

void APlayerControllerGreatSword::InputRKeyStart()
{
	StopMovement();

	if (HitSucceeded())
	{
		FVector Dir = GetCursorHitResult().Location - GetPawn()->GetActorLocation();
		Dir = Dir.GetSafeNormal();
		FRotator Rot = Dir.Rotation();
		Rot.Pitch = 0.0f;
		GetPawn()->SetActorRotation(Rot);
	}

	m_Player->SetPlayerAnimState(GreatSwordAnimState::RKey);
}

void APlayerControllerGreatSword::InputRKeyTriggered()
{
	if (m_Player->m_AnimState != GreatSwordAnimState::RKey)
	{
		return;
	}

	if (HitSucceeded())
	{
		FVector Dir = GetCursorHitResult().Location - GetPawn()->GetActorLocation();
		Dir = Dir.GetSafeNormal();
		FRotator Rot = Dir.Rotation();
		Rot.Pitch = 0.0f;
		GetPawn()->SetActorRotation(Rot);
	}
}
