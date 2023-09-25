// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../PlayerAnimState.h"
#include "GreatSwordAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UGreatSwordAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UGreatSwordAnimInstance();

protected:

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _DeltaSecond) override;

public:
	//FOR DELEGATE
	UFUNCTION()
	void MontageBlendOut(UAnimMontage* _Anim, bool _Inter);

	void JumpToSection(int32 SectionIndex);

	FName GetNormalAttackMontageName(int32 SectionIndex);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AllAnimations, meta = (AllowPrivateAccess = "true"))
	TMap<GreatSwordAnimState, class UAnimMontage*> m_AllAnimations;

	class UAnimMontage* m_CurrentMontage;

	class AGreatSwordCharacter* m_Player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AllAnimations, meta = (AllowPrivateAccess = "true"))
	GreatSwordAnimState m_AnimState = GreatSwordAnimState::IDLE;
	
private:

	int32 AttackSectionIndex = 0;
};
