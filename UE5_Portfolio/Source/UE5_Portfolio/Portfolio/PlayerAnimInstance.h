// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Global/MainPlayerAnimState.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPlayerAnimInstance();
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _DeltaSecond) override;

public:

	UFUNCTION()
	void MontageEnd(UAnimMontage* _Anim, bool _Inter);


private:
	
	TMap<PlayerAnimState, class UAnimMontage*> AllAnimations;

	UPROPERTY(EditAnywhere)
	PlayerAnimState AnimState = PlayerAnimState::IDLE;

	float CurrentPawnSpeed;
};
