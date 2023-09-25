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

	OnMontageBlendingOut.AddDynamic(this, &UGreatSwordAnimInstance::MontageBlendOut);
	OnPlayMontageNotifyBegin.AddDynamic(this, &UGreatSwordAnimInstance::AnimNotifyBegin);
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
		if (CurrentMontage == m_AllAnimations[GreatSwordAnimState::CKey])
		{
			JumpToSection(AttackSectionIndex);
			AttackSectionIndex = (AttackSectionIndex + 1) % 3;
		}
	}

}

void UGreatSwordAnimInstance::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == FName("Burst"))
	{
		FTransform Transform = m_Player->GetTransform();
		Transform.SetLocation(m_Player->GetActorLocation() + m_Player->GetActorForwardVector() * 150);
		FRotator Rot = Transform.GetRotation().Rotator();
		Rot.Pitch = 0.0f;
		Transform.SetRotation(Rot.Quaternion());
		GetWorld()->SpawnActor<AActor>(*m_Player->m_SkillActors.Find(FName("Burst")), Transform);
	}

	if (NotifyName == FName("WKeySkill"))
	{
		FTransform Transform = m_Player->GetTransform();
		GetWorld()->SpawnActor<AActor>(*m_Player->m_SkillActors.Find(FName("WKeySkill")), Transform);
	}

	if (NotifyName == FName("RKeySkill"))
	{
		FTransform Transform = m_Player->GetTransform();
		Transform.SetLocation(m_Player->GetActorLocation() + m_Player->GetActorForwardVector() * 300);
		FRotator Rot = Transform.GetRotation().Rotator();
		Rot.Pitch = 0.0f;
		Transform.SetRotation(Rot.Quaternion());
		GetWorld()->SpawnActor<AActor>(*m_Player->m_SkillActors.Find(FName("RKeySkill")), Transform);
		
	}

	if (NotifyName == FName("RKeyCharge"))
	{
		FTransform Transform = m_Player->GetTransform();
		FVector vec = m_Player->GetActorLocation();
		vec.Z = m_Player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		Transform.SetLocation(vec);
		GetWorld()->SpawnActor<AActor>(*m_Player->m_SkillActors.Find(FName("RKeyCharge")), Transform);
		
	}
}

void UGreatSwordAnimInstance::MontageBlendOut(UAnimMontage* _Anim, bool _Inter)
{
	if (_Anim == m_AllAnimations[GreatSwordAnimState::CKey])
	{
		m_AnimState = GreatSwordAnimState::IDLE;
		m_Player->SetPlayerAnimState(m_AnimState);
		FRotator OriginRotation = m_Player->GetActorRotation();
		OriginRotation.Pitch = 0.0f;
		m_Player->SetActorRotation(OriginRotation);
	}

	if (_Anim == m_AllAnimations[GreatSwordAnimState::QKey])
	{
		m_AnimState = GreatSwordAnimState::IDLE;
		m_Player->SetPlayerAnimState(m_AnimState);
	}

	if (_Anim == m_AllAnimations[GreatSwordAnimState::WKey])
	{
		m_AnimState = GreatSwordAnimState::IDLE;
		m_Player->SetPlayerAnimState(m_AnimState);
		FRotator OriginRotation = m_Player->GetActorRotation();
		OriginRotation.Pitch = 0.0f;
		m_Player->SetActorRotation(OriginRotation);
	}

	if (_Anim == m_AllAnimations[GreatSwordAnimState::EKey])
	{
		m_AnimState = GreatSwordAnimState::IDLE;
		m_Player->SetPlayerAnimState(m_AnimState);
		FRotator OriginRotation = m_Player->GetActorRotation();
		OriginRotation.Pitch = 0.0f;
		m_Player->SetActorRotation(OriginRotation);
	}

	if (_Anim == m_AllAnimations[GreatSwordAnimState::RKey])
	{
		m_AnimState = GreatSwordAnimState::IDLE;
		m_Player->SetPlayerAnimState(m_AnimState);
		FRotator OriginRotation = m_Player->GetActorRotation();
		OriginRotation.Pitch = 0.0f;
		m_Player->SetActorRotation(OriginRotation);
	}

	if (_Anim == m_AllAnimations[GreatSwordAnimState::DASH])
	{
		m_AnimState = GreatSwordAnimState::IDLE;
		m_Player->SetPlayerAnimState(m_AnimState);
	}
	/*if (_Anim == m_AllAnimations[GreatSwordAnimState::JOG_FWD])
	{
		m_AnimState = GreatSwordAnimState::;
		m_Player->SetPlayerAnimState(m_AnimState);
	}*/
}

void UGreatSwordAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetNormalAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, m_AllAnimations[GreatSwordAnimState::CKey]);
}

FName UGreatSwordAnimInstance::GetNormalAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("%d"), SectionIndex));
}
