// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MainPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerAnimInstance.h"
#include "PortfolioHUD.h"

APortfolioPlayerController::APortfolioPlayerController()
{
	bShowMouseCursor = true;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.0f;

}

void APortfolioPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<AMainPlayer>(GetPawn());
	if (MyCharacter == nullptr)
	{
		return;
	}


	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	


}



void APortfolioPlayerController::SetupInputComponent()
{

	Super::SetupInputComponent();

	static bool bBindingsAdded = false;

	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("ActionKeyC"), EKeys::C));
	}


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(
			SetDestinationClickAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputStarted
		);
		EnhancedInputComponent->BindAction(
			SetDestinationClickAction, ETriggerEvent::Triggered, this, &APortfolioPlayerController::OnSetDestinationTriggered
		);
		EnhancedInputComponent->BindAction(
			SetDestinationClickAction, ETriggerEvent::Completed, this, &APortfolioPlayerController::OnSetDestinationReleased
		);
		EnhancedInputComponent->BindAction(
			SetDestinationClickAction, ETriggerEvent::Canceled, this, &APortfolioPlayerController::OnSetDestinationReleased
		);
		EnhancedInputComponent->BindAction(
			InputCButtonAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputCKeyPressed
		);
		EnhancedInputComponent->BindAction(
			InputCButtonAction, ETriggerEvent::Triggered, this, &APortfolioPlayerController::OnInputCKeyPressed
		);
		EnhancedInputComponent->BindAction(
			InputCButtonAction, ETriggerEvent::Ongoing, this, &APortfolioPlayerController::OnInputCKeyPressed
		);

		//UI Visiblity TEST
		EnhancedInputComponent->BindAction(
			InputGButtonAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputTestUIKeyPressed
		);
		/*EnhancedInputComponent->BindAction(
			InputGButtonAction, ETriggerEvent::Triggered, this, &APortfolioPlayerController::OnInputTestUIKeyPressed
		);*/


		/*EnhancedInputComponent->BindAction(
			InputCButtonAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputCKeyPressed
		);
		EnhancedInputComponent->BindAction(
			InputCButtonAction, ETriggerEvent::Triggered, this, &APortfolioPlayerController::OnInputCKeyPressed
		);*/
	}
	//InputComponent->BindAction("ActionKeyC", EInputEvent::IE_Pressed, this, &APortfolioPlayerController::OnInputCKeyPressed);
	
}

void APortfolioPlayerController::OnInputStarted()
{
	//StopMovement(this);
	StopMovement();
}

//every frame when the input is held down
void APortfolioPlayerController::OnSetDestinationTriggered()
{
	if (MyCharacter->AnimState == PlayerAnimState::NORMAL_ATTACK)
	{
		//º¸·ù
		//GetPawn()->SetActorotation(FRotator(GetPawn()->GetActorRotation()));
		return;
		
	}
	

	int a = 0;
	//Input is being Pressed
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

void APortfolioPlayerController::OnSetDestinationReleased()
{
	//If it was a short press

	if (FollowTime <= ShortPressThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		
	}

	FollowTime = 0.0f;
}

void APortfolioPlayerController::OnInputCKeyPressed()
{
	StopMovement();

	FHitResult Hit;
	bool bHitSuccessful = false;
	
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	APawn* ControlledPawn = GetPawn();
	
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		FRotator Rot = WorldDirection.Rotation();
		Rot.Roll = 0.0f;
		Rot.Pitch = 0.0;
		ControlledPawn->SetActorRotation(Rot);
	}



	AMainPlayer* temp = Cast<AMainPlayer>(GetPawn());
	if (temp == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) PlayerController : Can not found MainPlayer in Controller"), __FUNCTION__, __LINE__);
		return;
	}
	temp->AnimState = PlayerAnimState::NORMAL_ATTACK;
	return; 
}

void APortfolioPlayerController::OnInputCKeyReleased()
{
	return;
}

void APortfolioPlayerController::OnInputTestUIKeyPressed()
{
	int a = 0;
	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

	if (HUD == nullptr && HUD->IsValidLowLevel())
	{
		return;
	}

	HUD->GetMainWidget()->TestWindowVisibilitySwitch();
}



