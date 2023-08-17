// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "Kismet/GameplayStatics.h"
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


	OnMontageBlendingOut.AddDynamic(this, &UMyAnimInstance::MontageEnd);
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

	if (CurrentMontage == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) AnimInstance : Can not found Anim_Montage."), __FUNCTION__, __LINE__);
		return;
	}

	if (!Montage_IsPlaying(CurrentMontage))
	{
		Montage_Play(CurrentMontage, 1.0f);
	}
	
}

void UMyAnimInstance::MontageEnd(UAnimMontage* _Anim, bool _Inter)
{
	if (m_Player == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) MainPlayer AnimInstance : MainPlayer is nullptr"), __FUNCTION__, __LINE__);
		return;
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
}

bool UMyAnimInstance::AnimCancelCheck(MyPlayerAnimState _State)
{
	if (_State == MyPlayerAnimState::DASH)
	{
		return false;
	}
	


	return true;
}
