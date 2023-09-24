// Fill out your copyright notice in the Description page of Project Settings.


#include "Skillwidget.h"

void USkillwidget::NativeConstruct()
{
}

void USkillwidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	m_CoolDownValue -= (1.0f * GetWorld()->GetDeltaSeconds());
	
}
