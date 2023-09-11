// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStatComponent.h"
#include "../../Global/TopDownGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Data/MonsterData.h"


// Sets default values for this component's properties
UMonsterStatComponent::UMonsterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;

	m_Level = 1;

	// ...
}


// Called when the game starts
void UMonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetLevel(m_Level);
	
}


// Called every frame
void UMonsterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMonsterStatComponent::SetLevel(int32 _Level)
{
	auto GameInstance = Cast<UTopDownGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance)
	{
		auto MonsterData = GameInstance->GetNormalMonsterData(MeleeMonsterName);

		if (MonsterData)
		{
			m_Level = MonsterData->Level;
			SetLevel(m_Level);
			m_MaxHp = MonsterData->MaxHp;
			m_OffensivePower = MonsterData->OffensivePower;
		}

	}
}

void UMonsterStatComponent::SetHp(int32 _Hp)
{
	m_CurrentHp = _Hp;
	if (m_CurrentHp < 0)
	{
		m_CurrentHp = 0;
	}

	OnHpChanged.Broadcast();
}

void UMonsterStatComponent::OnAttacked(float _DamageAmount)
{
	int32 NewHp = m_CurrentHp - _DamageAmount;
	SetHp(NewHp);
}

