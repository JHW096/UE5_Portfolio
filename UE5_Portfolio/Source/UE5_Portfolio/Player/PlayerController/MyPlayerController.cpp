// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Player/Character/PlayerCharacter.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.0f;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Get_Possessed_Character
	Player = Cast<APlayerCharacter>(GetPawn());
	if (Player == nullptr)
	{
		int a = 0;
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) PlayerCharacter == Nullptr"), __FUNCTION__, __LINE__);
	}

	//EnhancedInputSystem_MappingContext
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	static bool bBindingsAdded = false;

	if (!bBindingsAdded)
	{
		bBindingsAdded = true;
	}

	//BIND_KEY
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//PLAYER_MOVE
		{
			EnhancedInputComponent->BindAction(
				SetDestinationClickAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputStarted
			);
			EnhancedInputComponent->BindAction(
				SetDestinationClickAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnSetDestinationTriggered
			);
			EnhancedInputComponent->BindAction(
				SetDestinationClickAction, ETriggerEvent::Completed, this, &AMyPlayerController::OnSetDestinationReleased
			);
			EnhancedInputComponent->BindAction(
				SetDestinationClickAction, ETriggerEvent::Canceled, this, &AMyPlayerController::OnSetDestinationReleased
			);
		}

		//PLAYER_DASH
		{
			EnhancedInputComponent->BindAction(
				InputSpaceAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputSpaceKeyPressed
			);
		}

		//PLAYER_INPUT_C_KEY_PRESSED_NORMAL_ATTACK
		{
			EnhancedInputComponent->BindAction(
				InputCKeyAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputCKeyPressed
			);
		}
	}
}

//void AMyPlayerController::PlayerTick(float _DeltaSeconds)
//{
//	Super::PlayerTick(_DeltaSeconds);
//
//	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
//	{
//
//	}
//
//}

void AMyPlayerController::OnInputStarted()
{
	
}

void AMyPlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds();

	//Where the Player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	APawn* ControlledPawn = GetPawn();
	//GetPawn nullptr check
	if (ControlledPawn != nullptr)
	{
		//WorldDirection = FVector(Hit Location, MainPlayer Location) NormalVector
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0f, false);
	}
}

void AMyPlayerController::OnSetDestinationReleased()
{
	if (FollowTime <= ShortPressThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	}

	FollowTime = 0.0f;
}

void AMyPlayerController::OnInputSpaceKeyPressed()
{
	/*if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		CachedDestination = m_HitResult.Location;
	}

	const FVector ForwardDir = m_HitResult.Location.GetSafeNormal();

	Player->LaunchCharacter(ForwardDir * 1000.0f, true, false);*/
	
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FRotator Rot = FRotator::ZeroRotator;
		FVector Dir = (m_HitResult.Location - Player->GetActorLocation()).GetSafeNormal();
		Rot.Yaw = Dir.Rotation().Yaw;
		Player->SetActorRotation(Rot);
	}
	StopMovement();
	Player->m_AnimState = MyPlayerAnimState::DASH;
}

void AMyPlayerController::OnInputCKeyPressed()
{
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FRotator Rot = FRotator::ZeroRotator;
		FVector Dir = (m_HitResult.Location - Player->GetActorLocation()).GetSafeNormal();
		Rot.Yaw = Dir.Rotation().Yaw;
		Player->SetActorRotation(Rot);
	}
	StopMovement();
	Player->m_AnimState = MyPlayerAnimState::NORMAL_ATTACK_GUN;
}


