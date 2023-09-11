// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterWidget.h"
#include "MonsterStatComponent.h"
#include "Components/ProgressBar.h"

void UMonsterWidget::BindHp(UMonsterStatComponent* StatComp)
{
	m_CurrentStatComp = StatComp;
	StatComp->OnHpChanged.AddUObject(this, &UMonsterWidget::UpdateHp);
}

void UMonsterWidget::UpdateHp()
{
	if (m_CurrentStatComp.IsValid())
	{
		int a = 0;
		PB_HpBar->SetPercent(m_CurrentStatComp->GetMonsterHPRatio());
	}
}
