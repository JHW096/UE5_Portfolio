// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordAnimInstance.h"
#include "../Character/GreatSwordCharacter.h"

UGreatSwordAnimInstance::UGreatSwordAnimInstance()
{
}

void UGreatSwordAnimInstance::NativeBeginPlay()
{
	m_Player = Cast<AGreatSwordCharacter>(TryGetPawnOwner());
	if (m_Player == nullptr)
	{
		return;
	}
	m_AllAnimations = m_Player->m_AllAnimations;
}

void UGreatSwordAnimInstance::NativeUpdateAnimation(float _DeltaSecond)
{
	if (m_AllAnimations.Num() == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) AnimInstance : No one Animation."), __FUNCTION__, __LINE__);
		return;
	}

	m_AnimState = m_Player->m_AnimState;

	UAnimMontage* CurrentMontage = m_AllAnimations[m_AnimState];
	m_CurrentMontage = CurrentMontage;

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

void UGreatSwordAnimInstance::MontageBlendOut(UAnimMontage* _Anim, bool _Inter)
{
}

void UGreatSwordAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetNormalAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, m_AllAnimations[GreatSwordAnimState::CKey]);
}

FName UGreatSwordAnimInstance::GetNormalAttackMontageName(int32 SectionIndex)
{
	return FName();
}
