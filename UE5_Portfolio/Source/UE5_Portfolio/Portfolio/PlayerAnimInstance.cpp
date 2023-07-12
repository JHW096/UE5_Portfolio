// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MainPlayer.h"


UPlayerAnimInstance::UPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UPlayerAnimInstance::MontageEnd);

	AMainPlayer* Player = Cast<AMainPlayer>(GetOwningActor());

	if (Player == nullptr && Player->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : AnimInstance : TryGetPawnOnwer Faild"), __FUNCTION__, __LINE__);
		return;
	}

	AllAnimations = Player->AllAnimations;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float _DeltaSecond)
{
	Super::NativeUpdateAnimation(_DeltaSecond);
	
	if (AllAnimations.Num() == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) AnimInstance : No one Animation."), __FUNCTION__, __LINE__);
		return;
	}

	AMainPlayer* MainPlayer = Cast<AMainPlayer>(GetOwningActor());
	if (MainPlayer == nullptr || MainPlayer->IsValidLowLevel() == false)
	{
		return;

	}

	CurrentPawnSpeed = MainPlayer->GetVelocity().Size();

	AnimState = MainPlayer->AnimState;

	UAnimMontage* CurrentMontage = AllAnimations[AnimState];

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

void UPlayerAnimInstance::MontageEnd(UAnimMontage* _Anim, bool _Inter)
{
	AMainPlayer* Player = Cast<AMainPlayer>(GetOwningActor());

	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) MainPlayer AnimInstance : MainPlayer is nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	if (AllAnimations[PlayerAnimState::NORMAL_ATTACK] == _Anim)
	{
		AnimState = PlayerAnimState::IDLE;
		Player->AnimState = AnimState;
		Montage_Play(AllAnimations[PlayerAnimState::IDLE], 1.0f);
	}

}

