// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatusWidget.h"
#include "PlayerStatComponent.h"
#include "Components/ProgressBar.h"

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
