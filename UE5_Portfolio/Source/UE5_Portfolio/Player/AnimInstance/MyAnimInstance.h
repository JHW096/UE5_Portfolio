// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../PlayerAnimState.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */

UCLASS()
class UE5_PORTFOLIO_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UMyAnimInstance();

protected:

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _DeltaSecond) override;
	
public: 
	//FOR DELEGATE
	UFUNCTION()
	void MontageBlendOut(UAnimMontage* _Anim, bool _Inter);

	UFUNCTION()
	void MontagEnd(UAnimMontage* _Anim, bool _Inter);

public:

	void JumpToSection(int32 SectionIndex);

	FName GetNormalAttackMontageName(int32 SectionIndex);

	bool AnimCancelCheck(MyPlayerAnimState _State);

public:


public:

	FORCEINLINE class UAnimMontage* GetAnimMontage(MyPlayerAnimState _AnimState)
	{
		return AllAnimations[_AnimState];
	}

	FORCEINLINE int32 GetAttackSectionIndex()
	{
		return AttackSectionIndex;
	}

	FORCEINLINE class UAnimMontage* GetCurrentMontage()
	{
		return m_CurrentMontage;
	}

	FORCEINLINE TMap<MyPlayerAnimState, class UAnimMontage*> GetAllanimations()
	{
		return AllAnimations;
	}

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AllAnimations, meta = (AllowPrivateAccess = "true"))
	TMap<MyPlayerAnimState, class UAnimMontage*> AllAnimations;

	class UAnimMontage* m_CurrentMontage;

	class APlayerController* m_PlayerController;

	class APlayerCharacter* m_Player;

	MyPlayerAnimState m_AnimState = MyPlayerAnimState::IDLE;

	float CurrentPawnSpeed = 0.0f;

	bool m_CancelAnimCheck;

	int32 AttackSectionIndex = 0;
};
