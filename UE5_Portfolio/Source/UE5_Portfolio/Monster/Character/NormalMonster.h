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

private:

	UPROPERTY(Category = "AnimValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int AnimState = 0;

	UPROPERTY(Category = "AnimValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, class UAnimMontage*> AllAnimations;

};
