// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerHpChanged);
DECLARE_MULTICAST_DELEGATE(FOnPlayerMpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_PORTFOLIO_API UPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: 
	//Setter

	//PlayerStat
	void SetPlayerLevel(int32 _Level);
	void SetPlayerHp(int32 _Hp);
	void SetPlayerMp(int32 _Mp);
	
	//Offensive Data

	void SetPlayerBulletPower(int32 _Power);
	void SetSnipeShootPower(int32 _Power);

public:
	//getter

	FORCEINLINE int32 GetPlayerLevel() { return m_Level; }

	FORCEINLINE int32 GetPlayerMaxHp()
	{
		return m_MaxHp;
	}

	FORCEINLINE int32 GetPlayerMaxMp()
	{
		return m_MaxMp;
	}

	FORCEINLINE int32 GetPlayerFristBulletPower()
	{
		return m_FristBulletPower;
	}

	FORCEINLINE int32 GetPlayerSecondBulletPower()
	{
		return m_SecondBulletPower;
	}

	FORCEINLINE int32 GetPlayerThirdBulletPower()
	{
		return m_ThirdBulletPower;
	}

	FORCEINLINE int32 GetPlayerSnipeShootPower()
	{
		return m_SnipeShootPower;
	}

	FORCEINLINE int32 GetPlayerSnipeShootMp()
	{
		return m_SnipeShootMp;
	}

	FORCEINLINE float GetPlayerHpRatio()
	{
		return  m_CurrentHp / float(m_MaxHp);
	}

	FORCEINLINE float GetPlayerMpRatio()
	{
		return m_CurrentMp / float(m_MaxMp);
	}
	
private:

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_Level;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_MaxHp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_CurrentHp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_MaxMp;
		
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_CurrentMp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_FristBulletPower;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_SecondBulletPower;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_ThirdBulletPower;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_SnipeShootPower;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 m_SnipeShootMp;



	FName PlayerStatDataName = FName("PlayerStat");
public:

	FOnPlayerHpChanged OnPlayerHpChanged;

	FOnPlayerMpChanged OnPlayerMpChanged;
};
