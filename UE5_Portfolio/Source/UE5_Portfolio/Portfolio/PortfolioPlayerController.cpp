// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MainPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerAnimInstance.h"
#include "PortfolioHUD.h"
#include "Components/SphereComponent.h"
#include "../Player/FirstSkill.h"
#include "DrawDebugHelpers.h"
#include "../Player/SkillButtonPressed.h"

APortfolioPlayerController::APortfolioPlayerController()
{
	bShowMouseCursor = true;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.0f;


	///
	ChargeTime = 2.0f;

	/// Script / Engine.Blueprint'/Game/BP_PressedActor.BP_PressedActor'

	/*static ConstructorHelpers::FObjectFinder<ASkillButtonPressed> BP_W(
		TEXT("/Script/Engine.Blueprint'/Game/BP_PressedActor.BP_PressedActor_C'")
	);
	if (BP_W.Succeeded())
	{
		KeyWPressedActor2 = BP_W.Object;
	}*/
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
		
#pragma region PLAYER_CLICK_MOVE_BIND

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

#pragma endregion


		
		EnhancedInputComponent->BindAction(
			InputCButtonAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputCKeyPressed
		);
		EnhancedInputComponent->BindAction(
			InputCButtonAction, ETriggerEvent::Triggered, this, &APortfolioPlayerController::OnInputCKeyPressed
		);
		EnhancedInputComponent->BindAction(
			InputCButtonAction, ETriggerEvent::Ongoing, this, &APortfolioPlayerController::OnInputCKeyPressed
		);

#pragma region UI_VISIBILITY_BIND
		//UI Visiblity TEST
		EnhancedInputComponent->BindAction(
			InputGButtonAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputTestUIKeyPressed
		);

		//Inventory
		EnhancedInputComponent->BindAction(
			InputIButtonAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputIKeyPressed
		);

#pragma endregion


#pragma region SKILL_Q_KEY_BIND
		
		EnhancedInputComponent->BindAction(
			InputQButtonAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputQKeyPressed
		);

		EnhancedInputComponent->BindAction(
			InputQButtonAction, ETriggerEvent::Triggered, this, &APortfolioPlayerController::OnInputQKeyTriggered
		);

		/*EnhancedInputComponent->BindAction(
			InputQButtonAction, ETriggerEvent::Ongoing, this, &APortfolioPlayerController::OnInputQKeyTriggered
		);*/

		EnhancedInputComponent->BindAction(
			InputQButtonAction, ETriggerEvent::Completed, this, &APortfolioPlayerController::OnInputQKeyReleased
		);

		EnhancedInputComponent->BindAction(
			InputQButtonAction, ETriggerEvent::Canceled, this, &APortfolioPlayerController::OnInputQKeyReleased
		);



#pragma endregion
		

#pragma region SKILL_W_KEY_BIND

		EnhancedInputComponent->BindAction(
			InputWButtonAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputWKeyPressed
		);

#pragma endregion

#pragma region MOUSE_L_CLICK

		EnhancedInputComponent->BindAction(
			InputMouseLButtonAction, ETriggerEvent::Started, this, &APortfolioPlayerController::OnInputLMouseClicked
		);

#pragma endregion



	}
	
	
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

void APortfolioPlayerController::OnInputLMouseClicked()
{
	int a = 0;
	KeyWPressedActor2->Destroy();
	if (KeyWPressedActor2 != nullptr)
	{
		KeyWPressedActor2 = nullptr;
	}
	
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
	//StopMovement();

	//FHitResult Hit;
	//bool bHitSuccessful = false;

	//bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	//if (bHitSuccessful)
	//{
	//	//GetWorld()->SpawnActor();
	//	return;
	//}
	return;
}

void APortfolioPlayerController::OnInputQKeyPressed()
{
	ResetChargeTime();
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (bHitSuccessful)
	{
		FVector templocation = Hit.Location;
		templocation.Z += 1000.0f;
		FTransform temptrans;
		temptrans.SetLocation(templocation);
		if (tmp == nullptr)
		{
			return;
		}

		FVector Debug_SkillRange = templocation;
		Debug_SkillRange.Z = 0.0f;
	}
}

void APortfolioPlayerController::OnInputQKeyTriggered()
{
	ChargeTime += GetWorld()->GetDeltaSeconds();
	
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (bHitSuccessful)
	{
		FVector templocation = Hit.Location;
		templocation.Z += 1000.0f;
		FTransform temptrans;
		temptrans.SetLocation(templocation);
		if (tmp == nullptr)
		{
			return;
		}

		FVector Debug_SkillRange = templocation;
		Debug_SkillRange.Z = 0.0f;

		if (ChargeTime > 1.5f)
		{
			DrawDebugCylinder(
				GetWorld(), //World
				Debug_SkillRange, // Height start
				Debug_SkillRange + FVector{0.0f, 0.0f, 1.0f}, //Height End
				200.0f, // Radius
				100, // Segment
				FColor::Green, //DrawColor
				false,	//PersistenLines
				2.0f //Life Time
				//Depth
				//Thick
			);
		}

	}
		
}

void APortfolioPlayerController::OnInputQKeyReleased()
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (bHitSuccessful)
	{
		FVector templocation = Hit.Location;
		templocation.Z += 1000.0f;
		FTransform temptrans;
		temptrans.SetLocation(templocation);
		if (tmp == nullptr)
		{
			return;
		}
		if (ChargeTime > 1.5f)
		{
			GetWorld()->SpawnActor<AActor>(tmp, temptrans);
		}
		
	}
	ResetChargeTime();
}

void APortfolioPlayerController::OnInputQKeyCanceled()
{
	ResetChargeTime();
}

void APortfolioPlayerController::OnInputWKeyPressed()
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (bHitSuccessful)
	{
		FVector templocation = Hit.Location;
		FTransform temptrans;
		temptrans.SetLocation(templocation);
		if (KeyWPressedActor == nullptr)
		{
			return;
		}

		if (KeyWPressedActor2 == nullptr)
		{
			KeyWPressedActor2 = GetWorld()->SpawnActor<AActor>(KeyWPressedActor, temptrans);
		}
		else
		{
			return;
		}

	}

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

void APortfolioPlayerController::OnInputIKeyPressed()
{

	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

	if (HUD == nullptr && HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetMainWidget()->InventoryWindowVisibilitySwitch();

}



