// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _DeltaTime) override;


public:
	
	UFUNCTION()
	void MontageEnd(UAnimMontage* Anim, bool _Inter);

public: 

	UPROPERTY(Category = "AnimState", EditAnywhere, BlueprintReadWrite)
	int AnimState = 0;

	TMap<int, class UAnimMontage*> AllAnimations;

};
