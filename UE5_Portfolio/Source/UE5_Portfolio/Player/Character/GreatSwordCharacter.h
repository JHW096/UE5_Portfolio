// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownMoveCharacterBase.h"
#include "../PlayerAnimState.h"
#include "GreatSwordCharacter.generated.h"



UCLASS()
class UE5_PORTFOLIO_API AGreatSwordCharacter : public ATopDownMoveCharacterBase
{
	GENERATED_BODY()
public:

	AGreatSwordCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

public:

	FORCEINLINE class UPlayerStatComponent* GetStatComponent()
	{
		return m_StatCompoenent;
	}

	FORCEINLINE void SetPlayerAnimState(GreatSwordAnimState _AnimState)
	{
		m_AnimState = _AnimState;
	}

public:

	UPROPERTY(Category = "Animation_Value", EditAnywhere, BlueprintReadWrite)
	GreatSwordAnimState m_AnimState;

	UPROPERTY(Category = "Animation_Value", EditAnywhere, BlueprintReadWrite)
	TMap<GreatSwordAnimState, UAnimMontage*> m_AllAnimations;

private:

	class UPlayerStatComponent* m_StatCompoenent;

};
