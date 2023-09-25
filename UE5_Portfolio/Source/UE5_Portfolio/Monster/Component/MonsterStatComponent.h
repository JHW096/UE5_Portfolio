// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_PORTFOLIO_API UMonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	void SetLevel(int32 _Level);
	void SetHp(int32 _Hp);

	UFUNCTION(BlueprintCallable)
	void OnAttacked(float _DamageAmount);

	FORCEINLINE int32 GetMonsterLevel()
	{
		return m_Level; 
	}

	FORCEINLINE int32 GetMonsterCurrentHp()
	{
		return m_CurrentHp;
	}

	FORCEINLINE int32 GetMonsterMaxHp()
	{
		return m_MaxHp;
	}

	FORCEINLINE	float GetMonsterHPRatio()
	{
		return m_CurrentHp / float(m_MaxHp);
	}

	FORCEINLINE int32 GetMonsterOffensive()
	{
		return m_OffensivePower;
	}

private:

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_Level;
	
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_CurrentHp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_MaxHp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_OffensivePower;

	
	FName MeleeMonsterName = FName("NONE");

public:

	FOnHpChanged OnHpChanged;


};
