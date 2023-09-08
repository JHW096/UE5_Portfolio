// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "../PlayerController/MyPlayerController.h"
#include "../Character/PlayerCharacter.h"

UMyAnimInstance::UMyAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	m_PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	m_Player = Cast<APlayerCharacter>(GetOwningActor());
	
	if (m_Player == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%s(%u) APlayerChracter == Nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	AllAnimations = m_Player->AllAnimations;


	OnMontageBlendingOut.AddDynamic(this, &UMyAnimInstance::MontageBlendOut);
	OnPlayMontageNotifyBegin.AddDynamic(this, &UMyAnimInstance::AnimNotifyBegin);
	OnPlayMontageNotifyEnd.AddDynamic(this, &UMyAnimInstance::AnimNotifyBegin);
	


	m_LaserShotCast = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetLaserShotStart();
}

void UMyAnimInstance::NativeUpdateAnimation(float _DeltaSecond)
{
	Super::NativeUpdateAnimation(_DeltaSecond);

	if (AllAnimations.Num() == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) AnimInstance : No one Animation."), __FUNCTION__, __LINE__);
		return;
	}

	CurrentPawnSpeed = m_Player->GetVelocity().Size();

	m_AnimState = m_Player->m_AnimState;
		
	UAnimMontage* CurrentMontage = AllAnimations[m_AnimState];
	m_CurrentMontage = CurrentMontage;

	if (CurrentMontage == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) AnimInstance : Can not found Anim_Montage."), __FUNCTION__, __LINE__);
		return;
	}

	if (m_IsMontagePaused)
	{
		return;
	}

	if (!Montage_IsPlaying(CurrentMontage))
	{
		if (CurrentMontage == AllAnimations[MyPlayerAnimState::NORMAL_ATTACK_GUN])
		{
			Montage_Play(CurrentMontage, 1.0f);
			JumpToSection(AttackSectionIndex);
			AttackSectionIndex = (AttackSectionIndex + 1) % 3;
		}
		else
		{
			Montage_Play(CurrentMontage, 1.0f);
		}
	}
}

void UMyAnimInstance::MontageBlendOut(UAnimMontage* _Anim, bool _Inter)
{
	if (m_Player == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) MainPlayer AnimInstance : MainPlayer is nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	if (_Anim == AllAnimations[MyPlayerAnimState::JOG_FWD])
	{
		m_AnimState = MyPlayerAnimState::IDLE;
		m_Player->m_AnimState = m_AnimState;
		Montage_Play(AllAnimations[MyPlayerAnimState::IDLE], 1.0f);
	}


	if (_Anim == AllAnimations[MyPlayerAnimState::DASH])
	{
		m_AnimState = MyPlayerAnimState::IDLE;
		m_Player->m_AnimState = m_AnimState;
		FRotator RecorverRotationToRootMotion = m_Player->GetActorRotation();
		RecorverRotationToRootMotion.Pitch = 0.0;
		RecorverRotationToRootMotion.Yaw += 27.32;
		RecorverRotationToRootMotion.Roll = 0.0;
		m_Player->SetActorRotation(RecorverRotationToRootMotion);
		
		Montage_Play(AllAnimations[MyPlayerAnimState::IDLE], 1.0f);
	}

	if (_Anim == AllAnimations[MyPlayerAnimState::NORMAL_ATTACK_GUN])
	{
		m_AnimState = MyPlayerAnimState::IDLE;
		m_Player->m_AnimState = m_AnimState;
		Montage_Play(AllAnimations[MyPlayerAnimState::IDLE], 1.0f);
	}


	if (_Anim == AllAnimations[MyPlayerAnimState::NORMAL_ATTACK_SWORD])
	{
		m_AnimState = MyPlayerAnimState::IDLE;

		FRotator RecorverRotationToRootMotion = m_Player->GetActorRotation();
		RecorverRotationToRootMotion.Pitch = 0.0;
		RecorverRotationToRootMotion.Yaw += 27.32;
		RecorverRotationToRootMotion.Roll = 0.0;
		m_Player->SetActorRotation(RecorverRotationToRootMotion);


		m_Player->m_AnimState = m_AnimState;
		Montage_Play(AllAnimations[MyPlayerAnimState::IDLE], 1.0f);
	}

	if (_Anim == AllAnimations[MyPlayerAnimState::SKILL_W])
	{
		FRotator RecorverRotationToRootMotion = m_Player->GetActorRotation();
		RecorverRotationToRootMotion.Pitch = 0.0;
		RecorverRotationToRootMotion.Roll = 0.0;
		m_Player->SetActorRotation(RecorverRotationToRootMotion);
	}

	if (_Anim == AllAnimations[MyPlayerAnimState::SKILL_E])
	{
		m_AnimState = MyPlayerAnimState::IDLE;
		m_Player->m_AnimState = m_AnimState;

		FRotator RecorverRotationToRootMotion = m_Player->GetActorRotation();
		RecorverRotationToRootMotion.Pitch = 0.0f;
		m_Player->SetActorRotation(RecorverRotationToRootMotion);
		Montage_Play(AllAnimations[MyPlayerAnimState::IDLE], 1.0f);
	}

	if (_Anim == AllAnimations[MyPlayerAnimState::SNIPE_SHOOT])
	{
		FVector RecoveryRotation = m_Player->GetActorLocation();
		RecoveryRotation.Z = 0.0f;
		RecoveryRotation.X = m_Player->GetActorForwardVector().X;
		RecoveryRotation.Y = m_Player->GetActorForwardVector().Y;
		m_Player->SetActorRotation(RecoveryRotation.Rotation());
		m_Player->m_AnimState = MyPlayerAnimState::IDLE;

		Cast<AMyPlayerController>(m_PlayerController)->SetRKeyOngoing(false);

	}

}

void UMyAnimInstance::MontagEnd(UAnimMontage* _Anim, bool _Inter)
{
	if (_Anim == AllAnimations[MyPlayerAnimState::NORMAL_ATTACK_GUN])
	{
		AttackSectionIndex = 0;
	}

	if (_Anim == AllAnimations[MyPlayerAnimState::SNIPE_SHOOT])
	{
		Cast<AMyPlayerController>(m_PlayerController)->SetRKeyOngoing(false);
	}
}

void UMyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetNormalAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AllAnimations[MyPlayerAnimState::NORMAL_ATTACK_GUN]);
}

FName UMyAnimInstance::GetNormalAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Combo%d"), SectionIndex + 1));
}

bool UMyAnimInstance::AnimCancelCheck(MyPlayerAnimState _State)
{
	if (_State == MyPlayerAnimState::DASH)
	{
		return false;
	}
	


	return true;
}



void UMyAnimInstance::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	
	if (NotifyName == TEXT("Pause"))
	{
		int a = 0;
		m_IsMontagePaused = true;
		UAnimMontage* anim = GetCurrentMontage();
		Montage_Pause(GetCurrentMontage());

		FTransform SpawnTransform;
		SpawnTransform = m_Player->GetMesh()->GetSocketTransform(TEXT("WP_Gun_Socket"));
		SpawnTransform.SetRotation(m_Player->GetActorForwardVector().Rotation().Quaternion());
		
		GetWorld()->SpawnActor<AActor>(m_LaserShotCast, SpawnTransform);
	}

	if (NotifyName == TEXT("Pause_SnipeShoot"))
	{
		m_IsMontagePaused = true;
		UAnimMontage* anim = GetCurrentMontage();
		Montage_Pause(anim);
	}

}
