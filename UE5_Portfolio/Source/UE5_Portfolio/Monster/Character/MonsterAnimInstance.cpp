// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "NormalMonster.h"

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OnMontageBlendingOut.AddDynamic(this, &UMonsterAnimInstance::MontageEnd);
}

void UMonsterAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	if (AllAnimations.Num() == 0)
	{
		return;
	}

	ANormalMonster* Monster = Cast<ANormalMonster>(GetOwningActor());

	if (Monster == nullptr && Monster->IsValidLowLevel() == false)
	{
		return;
	}

	AnimState = Monster->GetAnimState();

	class UAnimMontage* Montage = AllAnimations[AnimState];

	if (Montage == nullptr)
	{
		return;
	}

	if (Montage_IsPlaying(Montage) == false)
	{
		Montage_Play(Montage, 1.0f);
	}

}

void UMonsterAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{
}
