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
#include "../Skill/Skill_AreaShotStart.h"
#include "../Skill/Skill_AreaShotDecal.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/Layout/Anchors.h"
#include "../../UI/Skill/PlayerSkillTileViewWidget.h"
#include "../../UI/Skill/PlayerSkillWidget.h"
#include "../../UI/Skill/PlayerSkillWidgets.h"
#include "Components/Button.h"




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

	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &AMyPlayerController::TimerDown, 0.2f, true);
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

		//PLAYER_INPUT_E_KEY_SKILL 
		{
			EnhancedInputComponent->BindAction(
				InputEKeyAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputEKeyPressed
			);
		}

		//PLAYER_INPUT_R_KEY_SKILL
		{

			EnhancedInputComponent->BindAction(
				InputRKeyAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputRKeyStarted
			);

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


		//PLAYER_INPUT_F_KEY_SKILL
		{
			EnhancedInputComponent->BindAction(
				InputFKeyAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputFKeyPressed
			);
		}

		//PLAYER_INPUT_I_KEY_SKILL
		{
			EnhancedInputComponent->BindAction(
				InputIKeyAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputIKeyPressed
			);
		}


		//PLAYER_L_MOUSE_BUTTON_
		{
			EnhancedInputComponent->BindAction(
				InputLMouseAction, ETriggerEvent::Started, this, &AMyPlayerController::OnMouseLButtonClicked
			);
		}

		//RKeyUI
		{
			EnhancedInputComponent->BindAction(
				InputRKeyAction, ETriggerEvent::Started, this, &AMyPlayerController::RKeyPressedUI
			);
		}
	}
}

void AMyPlayerController::PlayerTick(float _DeltaSeconds)
{
	Super::PlayerTick(_DeltaSeconds);

	int a = 0;

	if (R_Key_IsCooling == true)
	{
		R_Key_CoolTime -= (1.0f * _DeltaSeconds);
		R_Key_Ongoingtime -= (1.0f * _DeltaSeconds);
		/*if (m_PlayerSkillWidgets == nullptr)
		{
			return;
		}
		else
		{
			m_PlayerSkillWidgets->GetPlayerWidgetElement(3)->GetProgressBar()->SetPercent(R_Key_CoolTime / 10.0f);
		}*/
	}
	else // R_Key_IsCooling == false
	{
		SnipeShotCount = 1;
		R_StartedButton = false;
	}

	if (R_Key_CoolTime <= 0.0f)
	{
		R_Key_CoolTime = 10.0f;
		R_Key_Ongoingtime = 3.0f;
		R_Key_IsCooling = false;
	}

	

	/*m_PlayerSkillWidgets->SetCoolTimeReduce2(3, _DeltaSeconds);
	m_PlayerSkillWidgets->SetSkillProgressBar(3);*/



	
//	UE_LOG(LogTemp, Warning, TEXT("%s(%u) : CoolTime : %f"), __FUNCTION__, __LINE__, R_Key_CoolTime);

}

void AMyPlayerController::OnInputStarted()
{
}

void AMyPlayerController::OnSetDestinationTriggered()
{
	if (Player->m_AnimState == MyPlayerAnimState::DASH)
	{
		return;
	}

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

	if (Player->m_AnimState == MyPlayerAnimState::SKILL_F)
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
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		/*ControlledPawn->AddMovementInput(WorldDirection, 1.0f, false);*/
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

	if (Player->m_AnimState == MyPlayerAnimState::SKILL_F)
	{
		return;
	}

	if (FollowTime <= ShortPressThreshold)
	{
		/*UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);*/
	}

	FollowTime = 0.0f;
}

void AMyPlayerController::OnInputSpaceKeyPressed()
{
	if (Player->m_AnimState == MyPlayerAnimState::JOG_FWD)
	{
		m_AnimInstance->Montage_Stop(0.1f, m_AnimInstance->GetAnimMontage(MyPlayerAnimState::JOG_FWD));
		StopMovement();
	}

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

void AMyPlayerController::OnInputEKeyPressed()
{
	if (m_OnArea == true)
	{
		return;
	}

	if (m_AreaShotDecal == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s(%u) m_AreaShot == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	m_OnArea = true;

	AActor* AreaShot = nullptr;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FTransform AreaShotTransform;
		AreaShotTransform.SetLocation(m_HitResult.Location);
		m_DecalActor = Cast<ASkill_AreaShotDecal>(GetWorld()->SpawnActor<AActor>(m_AreaShotDecal, AreaShotTransform));
	}
}


void AMyPlayerController::OnInputRKeyStarted()
{

	if (R_Key_CoolTime < 5.0f)
	{
		return;
	}
	else
	{
		R_Key_IsCooling = true;
		R_StartedButton = true;
	}
}

void AMyPlayerController::OnInputRKeyPressed()
{
	if (R_StartedButton == false)
	{
		return;
	}

	if (SnipeShotCount != 1)
	{
		return;
	}

	if (R_Key_Ongoingtime <= 0.0f)
	{
		OnInputRKeyReleased();
		return;
	}



	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

	if (HUD == nullptr && HUD->IsValidLowLevel())
	{
		return;
	}

	HUD->GetMainWidget()->TurnOnCrossHair();

	UWidget* Widget = HUD->GetMainWidget()->GetWidgetFromName(TEXT("WBP_Skill_Snipe"));

	UUserWidget* Userwidget = Cast<UUserWidget>(Widget);	

	FVector2D ScreenPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()->GetGameViewport());
	

	FWidgetTransform WidgetTransform;
	WidgetTransform.Translation = ScreenPos;

	
	FVector2D MinusVector = { -0.05, -0.05 };
	WidgetTransform.Scale = CrossHairWidgetScale += MinusVector;

	if (CrossHairWidgetScale <= FVector2D{ 1.5, 1.5 })
	{
		CrossHairWidgetScale = { 1.5, 1.5 };


	}

	Widget->SetRenderTransform(WidgetTransform);

	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FVector Dir = m_HitResult.Location - Player->GetActorLocation();
		Dir.Z = 0.0;
		Player->SetActorRotation(Dir.Rotation());
	}


	if (Player->m_AnimState == MyPlayerAnimState::SNIPE_SHOOT)
	{
		return;
	}

	Player->m_AnimState = MyPlayerAnimState::SNIPE_SHOOT;
}

void AMyPlayerController::OnInputRKeyReleased()
{
	SnipeShotCount = 0;

	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

	if (HUD == nullptr && HUD->IsValidLowLevel())
	{
		return;
	}

	HUD->GetMainWidget()->TurnOffCrossHair();

	m_AnimInstance->SetMontagePaused(false);
	UAnimMontage* CurrentMontage = m_AnimInstance->GetCurrentMontage();
	m_AnimInstance->Montage_Stop(0.5f, CurrentMontage);

	CrossHairWidgetScale = { 5.0, 5.0 };

	Player->m_AnimState = MyPlayerAnimState::IDLE;
}

void AMyPlayerController::OnInputFKeyPressed()
{
	FVector Dir;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FRotator Rot = FRotator::ZeroRotator;
		Dir = (m_HitResult.Location - Player->GetActorLocation()).GetSafeNormal();
		Rot.Yaw = Dir.Rotation().Yaw;
		Player->SetActorRotation(Rot);
	}	

	Player->m_AnimState = MyPlayerAnimState::SKILL_F;
}

void AMyPlayerController::OnInputIKeyPressed()
{
	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

	if (HUD == nullptr && HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetMainWidget()->InventoryWindowVisibilitySwitch();
}

void AMyPlayerController::OnMouseLButtonClicked()
{
	
	if (m_DecalActor != nullptr)
	{
		m_DecalActor->Destroy();
		m_DecalActor = nullptr;
		m_OnArea = false;

		if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
		{
			FVector Dir = (m_HitResult.Location - Player->GetActorLocation()).GetSafeNormal();
			Player->SetActorRotation(Dir.Rotation());
		}


		Player->m_AnimState = MyPlayerAnimState::SKILL_E;
	}


	if (Player->m_AnimState == MyPlayerAnimState::SNIPE_SHOOT)
	{
		if (CrossHairWidgetScale != FVector2D{ 1.5, 1.5 })
		{
			return;
		}

		if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
		{

			FTransform SnipeShootSpawnTransform;
			SnipeShootSpawnTransform.SetLocation(m_HitResult.Location);
			if (SnipeShotCount == 1)
			{
				GetWorld()->SpawnActor<AActor>(m_SnipeShootActor, SnipeShootSpawnTransform);
				SnipeShotCount -= 1;
			}
			
			m_AnimInstance->SetMontagePaused(false);
			UAnimMontage* CurrentMontage = m_AnimInstance->GetCurrentMontage();
			m_AnimInstance->Montage_Resume(CurrentMontage);

			APortfolioHUD* HUD = GetHUD<APortfolioHUD>();

			if (HUD == nullptr && HUD->IsValidLowLevel())
			{
				return;
			}

			HUD->GetMainWidget()->TurnOffCrossHair();

			R_Key_Ongoing = false;
		}
		
	}
}

void AMyPlayerController::RKeyPressedUI()
{
	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();
	if (HUD == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) ControllerUI_HUD == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	UUserWidget* MainWidget = HUD->GetMainWidget();
	if (MainWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) MainWidget == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	UPlayerSkillWidgets* PlayerSkillWidgets = Cast<UPlayerSkillWidgets>(MainWidget->GetWidgetFromName(TEXT("WBP_PlayerSkillWidgets")));


	TimerBool = true;
//	PlayerSkillWidgets->FillAmountFullElement(3);
	
	/*UPlayerSkillWidget* SkillWidget = PlayerSkillWidgets->GetPlayerWidgetElement(3);
	UProgressBar* ProgressBar = SkillWidget->GetProgressBar();
	ProgressBar->SetPercent(R_Key_CoolTime);*/


	int a = 0;
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

void AMyPlayerController::AreaShotDecalDestroyed()
{
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FTransform SpawnTransform;
		FVector SpawnPos = m_HitResult.Location;
		SpawnPos.Z += 500.0f;
		SpawnTransform.SetLocation(SpawnPos);
		GetWorld()->SpawnActor<AActor>(m_AreaShotStart, SpawnTransform);
	}

}

void AMyPlayerController::TimerDown()
{
	m_TimerFloat -= 0.2f;
	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();
	if (HUD == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) ControllerUI_HUD == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	UUserWidget* MainWidget = HUD->GetMainWidget();
	if (MainWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) MainWidget == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	UPlayerSkillWidgets* PlayerSkillWidgets = Cast<UPlayerSkillWidgets>(MainWidget->GetWidgetFromName(TEXT("WBP_PlayerSkillWidgets")));
	PlayerSkillWidgets->GetPlayerWidgetElement(3)->SetCurrentCoolTime(m_TimerFloat);
	

}

//float AMyPlayerController::RKeyPercent()
//{
//	APortfolioHUD* HUD = GetHUD<APortfolioHUD>();
//	if (HUD == nullptr)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("%s(%u) ControllerUI_HUD == nullptr"), __FUNCTION__, __LINE__);
//		return -1.0f;
//	}
//
//	UUserWidget* MainWidget = HUD->GetMainWidget();
//	if (MainWidget == nullptr)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("%s(%u) MainWidget == nullptr"), __FUNCTION__, __LINE__);
//		return -1.0f;
//	}
//
//	UPlayerSkillTileViewWidget* PlayerSkillTileViewWidget = Cast<UPlayerSkillTileViewWidget>(MainWidget->GetWidgetFromName(TEXT("WBP_PlayerSkillTileViewWidget")));
//	if (PlayerSkillTileViewWidget == nullptr)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("%s(%u) PlayerSkillTileViewWidget == nullptr"), __FUNCTION__, __LINE__);
//		return -1.0f;
//	}
//
//	UPlayerSkillWidget* PlayerSkillWidget = PlayerSkillTileViewWidget->GetPlayerSkillWidgetFromTileView(0);
//
//	UProgressBar* ProgressBar = PlayerSkillWidget->GetProgressBar();
//
//	int32 CurrentCoolTime = PlayerSkillWidget->GetCurrentCoolTime();
//
//	float Percent = 10.0f / (float)PlayerSkillWidget->GetMaxCoolTime();
//
//	Percent -= (1.0f * GetWorld()->GetDeltaSeconds());
//	
//	if (Percent < 0.0f)
//	{
//		return 0.0f;
//	}
//
//	return Percent;
//
//}


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
