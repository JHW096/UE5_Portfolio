// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NormalMonster.generated.h"

UCLASS()
class UE5_PORTFOLIO_API ANormalMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANormalMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: 

	int GetAnimState()
	{
		return AnimState;
	}


	template<typename EnumType>
	void SetAnimState(EnumType _AnimState)
	{
		AnimState = static_cast<int>(_AnimState);
	}

	void SetAnimState(int _AnimState)
	{
		AnimState = _AnimState;
	}

public:

	template<typename EnumType>
	void PushAnimation(EnumType Index, class UAnimMontage* Montage)
	{
		PushAnimation(static_cast<int>(Index), Montage);
	}

	void PushAnimation(int Index, class UAnimMontage* Montage)
	{
		if (AllAnimations.Contains(Index) == true)
		{
			return;
		}
		AllAnimations.Add(Index, Montage);
	}

	template<typename EnumType>
	class UAnimMontage* GetAnimMontage(EnumType Index)
	{
		return GetAnimMontage(static_cast<int>(Index));
	}

	class UAnimMontage* GetAnimMontage(int Index)
	{
		if (AllAnimations.Contains(Index) == false)
		{
			return nullptr;
		}

		return AllAnimations[Index];
	}

private:

	UPROPERTY(Category = "AnimValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int AnimState = 0;

	UPROPERTY(Category = "AnimValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, class UAnimMontage*> AllAnimations;

	class UMonsterAnimInstance* MonsterAnimInstance = nullptr;
};
