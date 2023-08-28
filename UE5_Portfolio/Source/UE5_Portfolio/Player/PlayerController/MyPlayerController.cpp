// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "../AnimInstance/MyAnimInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Player/Character/PlayerCharacter.h"
#include "../../UI/MainWidget.h"
#include "../../Portfolio/PortfolioHUD.h"
#include "Components/ProgressBar.h"
#include "../../UI/CastingBarWidget.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"


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

	m_AnimInstance = Cast<UMyAnimInstance>(Player->GetMesh()->GetAnimInstance());
	if (m_AnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) Animinstance == Nullptr"), __FUNCTION__, __LINE__);
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
				InputCKeyAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnInputCKeyPressed
			);
		}
		
		//PLAYER_INPUT_Q_KEY_PRESSED_NORMAL_ATTACK
		{
			EnhancedInputComponent->BindAction(
				InputQKeyAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputQKeyPressed
			);
		}

		//PLAYER_INPUT_W_KEY_PRESSED_SECOND_SKILL
		{
			EnhancedInputComponent->BindAction(
				InputWKeyAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputWKeyPressed
			);

			EnhancedInputComponent->BindAction(
				InputWKeyAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnInputWKeyTriggered
			);

			EnhancedInputComponent->BindAction(
				InputWKeyAction, ETriggerEvent::Canceled, this, &AMyPlayerController::OnInputWKeyCanceled
			);

			EnhancedInputComponent->BindAction(
				InputWKeyAction, ETriggerEvent::Completed, this, &AMyPlayerController::OnInputWKeyCanceled
			);
		}

		//PLAYER_INPUT_R_KEY_SKILL
		{
			EnhancedInputComponent->BindAction(
				InputRKeyAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnInputRKeyPressed
			);

			EnhancedInputComponent->BindAction(
				InputRKeyAction, ETriggerEvent::Canceled, this, &AMyPlayerController::OnInputRKeyReleased
			);

			EnhancedInputComponent->BindAction(
				InputRKeyAction, ETriggerEvent::Completed, this, &AMyPlayerController::OnInputRKeyReleased
			);
		}


		//PLAYER_L_MOUSE_BUTTON_
		{
			EnhancedInputComponent->BindAction(
				InputLMouseAction, ETriggerEvent::Started, this, &AMyPlayerController::OnMouseLButtonClicked
			);
		}
	}
}

//void AMyPlayerController::PlayerTick(float _DeltaSeconds)
//{
//	Super::PlayerTick(_DeltaSeconds);
//
//}

void AMyPlayerController::OnInputStarted()
{
}

void AMyPlayerController::OnSetDestinationTriggered()
{
	if (Player->m_AnimState == MyPlayerAnimState::SNIPE_SHOOT)
	{
		return;
	}

	if (Player->m_AnimState == MyPlayerAnimState::NORMAL_ATTACK_GUN)
	{
		return;
	}

	if (Player->m_AnimState == MyPlayerAnimState::NORMAL_ATTACK_SWORD)
	{
		return;
	}

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
	if (Player->m_AnimState == MyPlayerAnimState::NORMAL_ATTACK_GUN)
	{
		return;
	}

	if (Player->m_AnimState == MyPlayerAnimState::NORMAL_ATTACK_SWORD)
	{
		return;
	}

	if (Player->m_AnimState == MyPlayerAnimState::SNIPE_SHOOT)
	{
		return;
	}

	if (FollowTime <= ShortPressThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	}

	FollowTime = 0.0f;
}

void AMyPlayerController::OnInputSpaceKeyPressed()
{
	if (Player->m_AnimState == MyPlayerAnimState::NORMAL_ATTACK_GUN)
	{
		m_AnimInstance->Montage_Stop(0.1f, m_AnimInstance->GetAnimMontage(MyPlayerAnimState::NORMAL_ATTACK_GUN));
	}

	if (Player->m_AnimState == MyPlayerAnimState::NORMAL_ATTACK_SWORD)
	{
		m_AnimInstance->Montage_Stop(0.1f, m_AnimInstance->GetAnimMontage(MyPlayerAnimState::NORMAL_ATTACK_SWORD));
	}

	if (Player->m_AnimState == MyPlayerAnimState::DASH)
	{
		return;
	}
	
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FRotator Rot = FRotator::ZeroRotator;
		FVector Dir = (m_HitResult.Location - Player->GetActorLocation()).GetSafeNormal();
		float RecoveryRootMotionAngle = -27.32f;
		Rot.Yaw = Dir.Rotation().Yaw + RecoveryRootMotionAngle;
		Player->SetActorRotation(Rot);
	}
	Player->m_AnimState = MyPlayerAnimState::DASH;
}

void AMyPlayerController::OnInputCKeyPressed()
{
	if (Player->m_AnimState == MyPlayerAnimState::DASH)
	{
		return;
	}

	if (Player->m_AnimState == MyPlayerAnimState::NORMAL_ATTACK_GUN)
	{
		return;
	}

	if (Player->m_AnimState == MyPlayerAnimState::SNIPE_SHOOT)
	{
		return;
	}

	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FRotator Rot = FRotator::ZeroRotator;
		FVector Dir = (m_HitResult.Location - Player->GetActorLocation()).GetSafeNormal();
		Rot.Yaw = Dir.Rotation().Yaw;
		Player->SetActorRotation(Rot);
	}
	StopMovement();

	USceneComponent* BulletStartPosComp = Player->GetCapsuleComponent()->GetChildComponent(0);
	FTransform BulletPos = BulletStartPosComp->GetComponentTransform();
	
	/*if (m_AnimInstance->GetAttackSectionIndex() == 1)
	{
		GetWorld()->SpawnActor<AActor>(m_Bullet, BulletPos);
		GetWorld()->SpawnActor<AActor>(m_Bullet, BulletPos);
	}
	else
	{
		GetWorld()->SpawnActor<AActor>(m_Bullet, BulletPos);
	}*/
	Player->m_AnimState = MyPlayerAnimState::NORMAL_ATTACK_GUN;
}

void AMyPlayerController::OnInputQKeyPressed()
{
	if (Player->m_AnimState == MyPlayerAnimState::DASH)
	{
		return;
	}

	if (Player->m_AnimState == MyPlayerAnimState::NORMAL_ATTACK_SWORD)
	{
		return;
	}

	if (Player->m_AnimState == MyPlayerAnimState::SNIPE_SHOOT)
	{
		return;
	}

	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FRotator Rot = FRotator::ZeroRotator;
		FVector Dir = (m_HitResult.Location - Player->GetActorLocation()).GetSafeNormal();
		float RecoveryRootMotionAngle = -27.32f;
		Rot.Yaw = Dir.Rotation().Yaw + RecoveryRootMotionAngle;
		Player->SetActorRotation(Rot);
	}
	StopMovement();
	Player->m_AnimState = MyPlayerAnimState::NORMAL_ATTACK_SWORD;

}

void AMyPlayerController::OnInputWKeyPressed()
{
	
	
}

void AMyPlayerController::OnInputWKeyTriggered()
{
	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

	if (HUD == nullptr && HUD->IsValidLowLevel())
	{
		return;
	}

	float Percent = 
	Cast<UCastingBarWidget>(HUD->GetMainWidget()->GetWidgetFromName(TEXT("WBP_CastingBar")))->GetFillAmount();

	if (Percent >= 1.0f)
	{
		HUD->GetMainWidget()->TurnOffProgressBar();
		Player->m_AnimState = MyPlayerAnimState::IDLE;
		return;
	}

	HUD->GetMainWidget()->TurnOnProgressBar();


	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FRotator Rot = FRotator::ZeroRotator;
		FVector Dir = (m_HitResult.Location - Player->GetActorLocation()).GetSafeNormal();
		float RecoveryRootMotionAngle = -5.32f;
		Rot.Yaw = Dir.Rotation().Yaw; // +RecoveryRootMotionAngle;
		Player->SetActorRotation(Rot);
	}

	Player->m_AnimState = MyPlayerAnimState::SKILL_W;
}

void AMyPlayerController::OnInputWKeyCanceled()
{
	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

	if (HUD == nullptr && HUD->IsValidLowLevel())
	{
		return;
	}

	HUD->GetMainWidget()->TurnOffProgressBar();

	Cast<UCastingBarWidget>(HUD->GetMainWidget()->GetWidgetFromName(TEXT("WBP_CastingBar")))->FillReset();

	Player->m_AnimState = MyPlayerAnimState::IDLE;
}

void AMyPlayerController::OnInputRKeyPressed()
{
	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

	if (HUD == nullptr && HUD->IsValidLowLevel())
	{
		return;
	}

	HUD->GetMainWidget()->TurnOnCrossHair();

	UWidget* Widget = HUD->GetMainWidget()->GetWidgetFromName(TEXT("WBP_Skill_Snipe"));

	FVector2D ScreenPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()->GetGameViewport());
	

	FWidgetTransform WidgetTransform;
	WidgetTransform.Translation = ScreenPos;

	Widget->SetRenderTransform(WidgetTransform);

	Player->m_AnimState = MyPlayerAnimState::SNIPE_SHOOT;
}

void AMyPlayerController::OnInputRKeyReleased()
{
	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

	if (HUD == nullptr && HUD->IsValidLowLevel())
	{
		return;
	}

	HUD->GetMainWidget()->TurnOffCrossHair();

	Player->m_AnimState = MyPlayerAnimState::IDLE;
}

void AMyPlayerController::OnMouseLButtonClicked()
{
	if (Player->m_AnimState == MyPlayerAnimState::SNIPE_SHOOT)
	{
		if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
		{
			FTransform SnipeShootSpawnTransform;
			SnipeShootSpawnTransform.SetLocation(m_HitResult.Location);
			GetWorld()->SpawnActor<AActor>(m_SnipeShootActor, SnipeShootSpawnTransform);
		}
	}
}




void AMyPlayerController::OnShootNotify()
{
	/*USceneComponent* BulletStartPosComp = Player->GetCapsuleComponent()->GetChildComponent(0);
	FTransform BulletPos = BulletStartPosComp->GetComponentTransform();
	BulletPos.SetRotation(Player->GetCapsuleComponent()->GetComponentTransform().GetRotation());*/
	
	FTransform BulletPos = Player->GetMesh()->GetSocketTransform(TEXT("WP_Gun_Socket"));
	BulletPos.SetRotation(Player->GetCapsuleComponent()->GetComponentTransform().GetRotation()); 


	GetWorld()->SpawnActor<AActor>(m_Bullet, BulletPos);
}


//Other Source
	/*FTransform Transform;
	Transform.SetLocation(m_HitResult.Location);
	AActor* cross = nullptr;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		cross = GetWorld()->SpawnActor<AActor>(m_CrossHairActor, Transform);
	}

	TArray<UActorComponent*> Arr;
	UUserWidget* CrossHairWidget = nullptr;
	if (cross != nullptr)
	{
		cross->GetComponents(Arr);
	}

	for (const auto& component : Arr)
	{
		if (component->ComponentHasTag(TEXT("CrossHair")))
		{
			CrossHairWidget = Cast<UWidgetComponent>(component)->GetWidget();
		}

	}
	if (CrossHairWidget != nullptr)
	{
		CrossHairWidget->Visibility = ESlateVisibility::Visible;
	}
	*/
