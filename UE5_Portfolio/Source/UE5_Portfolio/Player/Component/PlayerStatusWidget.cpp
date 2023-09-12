// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatusWidget.h"
#include "PlayerStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "../PlayerController/MyPlayerController.h"


	

void UPlayerStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_RKeyButton->OnClicked.AddDynamic(this, &UPlayerStatusWidget::UpdateRKey);
}

void UPlayerStatusWidget::BindHp(UPlayerStatComponent* StatComponent)
{
	m_CurrentStatComp = StatComponent;
	StatComponent->OnPlayerHpChanged.AddUObject(this, &UPlayerStatusWidget::UpdateHp);
}

void UPlayerStatusWidget::BindMp(UPlayerStatComponent* StatComponent)
{
	m_CurrentStatComp = StatComponent;
	StatComponent->OnPlayerMpChanged.AddUObject(this, &UPlayerStatusWidget::UpdataMp);
}

void UPlayerStatusWidget::UpdateHp()
{
	if (m_CurrentStatComp.IsValid())
	{
		PB_PlayerHpBar->SetPercent(m_CurrentStatComp->GetPlayerHpRatio());
	}
}

void UPlayerStatusWidget::UpdataMp()
{
	if (m_CurrentStatComp.IsValid())
	{
		PB_PlayerMpBar->SetPercent(m_CurrentStatComp->GetPlayerMpRatio());
	}
}

void UPlayerStatusWidget::PlayerHitTestButtonPressed(UPlayerStatComponent* StatComponent)
{
	m_CurrentStatComp = StatComponent;

	int32 PlayerCurrentHp = m_CurrentStatComp->GetPlayerCurrentHp();
	PlayerCurrentHp -= 10;

	m_CurrentStatComp->SetPlayerHp(PlayerCurrentHp);
	
	UpdateHp();
}

void UPlayerStatusWidget::UpdateRKey()
{
	if (m_RKeyButton->bIsEnabled) 
	{
		m_RKeyButton->SetIsEnabled(false);
	}
	else 
	{
		m_RKeyButton->SetIsEnabled(true);
	}
	
}

