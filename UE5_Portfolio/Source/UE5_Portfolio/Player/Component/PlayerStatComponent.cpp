// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatComponent.h"
#include "../../Global/TopDownGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Data/PlayerStatData.h"

// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;

	m_Level = 1;

	// ...
}


// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetPlayerLevel(m_Level);
	// ...
	
}


// Called every frame
void UPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStatComponent::SetPlayerLevel(int32 _Level)
{
	auto GameInstance = Cast<UTopDownGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));


	if (GameInstance)
	{
		auto PlayerStatData = GameInstance->GetPlayerStatData(PlayerStatDataName);

		if (PlayerStatData)
		{
			m_Level = PlayerStatData->Level;
			SetPlayerHp(PlayerStatData->MaxHp);
			m_MaxHp = PlayerStatData->MaxHp;
			m_MaxMp = PlayerStatData->MaxMp;

			m_FristBulletPower = PlayerStatData->FristBulletPower;
			m_SecondBulletPower = PlayerStatData->SecondBulletPower;
			m_ThirdBulletPower = PlayerStatData->ThirdBulletPower;

			m_SnipeShootPower = PlayerStatData->SnipeShootPower;
			m_SnipeShootMp = PlayerStatData->SnipeShootMp;
		}

	}
}

void UPlayerStatComponent::SetPlayerHp(int32 _Hp)
{
	m_CurrentHp = _Hp;

	if (m_CurrentHp < 0) 
	{
		m_CurrentHp = 0;
	}

	OnPlayerHpChanged.Broadcast();

}

void UPlayerStatComponent::SetPlayerMp(int32 _Mp)
{
	//TODO_ 
	/*{
		if (CurrentMP < SkillMP) 
		{
			return
		}
	}*/
}

void UPlayerStatComponent::SetPlayerBulletPower(int32 _Power)
{
	m_FristBulletPower += _Power;
	m_SecondBulletPower += _Power;
	m_ThirdBulletPower +=_Power;

	m_SecondBulletPower += 2;
	m_ThirdBulletPower += 3;
}

void UPlayerStatComponent::SetSnipeShootPower(int32 _Power)
{
	m_SnipeShootPower += _Power;
}


