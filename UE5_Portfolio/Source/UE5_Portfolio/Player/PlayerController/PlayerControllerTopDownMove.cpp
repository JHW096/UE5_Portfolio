// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerTopDownMove.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

void APlayerControllerTopDownMove::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerControllerTopDownMove::PlayerTick(float _DeltaSeconds)
{
	Super::PlayerTick(_DeltaSeconds);
}

void APlayerControllerTopDownMove::SetupInputComponent()
{
	Super::SetupInputComponent();

	AddInputAction(FName("SetDestinationClickAction"), SetDestinationClickAction);

	//SetDestinaitionClickAction Binding
	{
		EnhancedInputComponent->BindAction(
			SetDestinationClickAction, ETriggerEvent::Started, this, &APlayerControllerTopDownMove::OnInputStarted
		);
		EnhancedInputComponent->BindAction(
			SetDestinationClickAction, ETriggerEvent::Triggered, this, &APlayerControllerTopDownMove::OnSetDestinationTriggered
		);
		EnhancedInputComponent->BindAction(
			SetDestinationClickAction, ETriggerEvent::Completed, this, &APlayerControllerTopDownMove::OnSetDestinationReleased
		);
		EnhancedInputComponent->BindAction(
			SetDestinationClickAction, ETriggerEvent::Canceled, this, &APlayerControllerTopDownMove::OnSetDestinationReleased
		);
	}
	
}

bool APlayerControllerTopDownMove::HitSucceeded()
{
	return GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_CursorHitResult) == true ? true : false;
}

void APlayerControllerTopDownMove::OnInputStarted()
{
	//TODO Print _Debug HitReuslt Value..
}

void APlayerControllerTopDownMove::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds();

	if (HitSucceeded())
	{
		SetCacheDestination(m_CursorHitResult.Location);
	}

	APawn* Pawn = GetPawn();
	//GetPawn nullptr check
	if (Pawn != nullptr)
	{
		//Prev Way to Move
		//WorldDirection = FVector(Hit Location, MainPlayer Location) NormalVector
		//ControlledPawn->AddMovementInput(WorldDirection, 1.0f, false);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	}

}

void APlayerControllerTopDownMove::OnSetDestinationReleased()
{
	FollowTime = 0.0f;
}


