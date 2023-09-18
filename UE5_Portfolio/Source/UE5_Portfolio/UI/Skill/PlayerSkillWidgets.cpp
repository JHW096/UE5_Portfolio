// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillWidgets.h"
#include "PlayerSkillWidget.h"
#include "../../Player/Data/PlayerSkillData.h"

void UPlayerSkillWidgets::NativeConstruct()
{
	Super::NativeConstruct();
	InitiallizePlayerSkillName();
	InitiallizeSkillWidget();

	SetPlayerWidgetElement(3, SkillNamesArray[3]);
}

void UPlayerSkillWidgets::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

UPlayerSkillWidget* UPlayerSkillWidgets::GetPlayerWidgetElement(size_t _index)
{
	if (_index < 0 || _index > PLAYERSKILLNUM)
	{
		return nullptr;
	}
	
	return m_PlayerSkillWidgetArray[_index];
}

void UPlayerSkillWidgets::SetPlayerWidgetElement(size_t _index, FName _Name)
{
	if (_index < 0 || _index > PLAYERSKILLNUM)
	{
		return;
	}

	UPlayerSkillWidget* SkillWidget = m_PlayerSkillWidgetArray[_index];
	if (SkillWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) SkillWidget == nullptr"), __FUNCTION__, __LINE__);
		return;
	}
	
	SkillWidget->SetPlayerSkill(_Name);
}

void UPlayerSkillWidgets::FillAmountFullElement(int32 _index)
{
	if (_index < 0 || _index > PLAYERSKILLNUM)
	{
		return;
	}

	m_PlayerSkillWidgetArray[_index]->GetProgressBar()->SetPercent(1.0f);

}

void UPlayerSkillWidgets::SetSkillProgressBar(int32 _Index)
{
	if (_Index < 0 || _Index > PLAYERSKILLNUM)
	{
		return;
	}

	m_PlayerSkillWidgetArray[_Index]->GetProgressBar()->SetPercent(m_SkillCoolTimePercent[_Index]);

	OnQButtonProgress.Broadcast();
}

void UPlayerSkillWidgets::SetCoolTimeReduce(int32 _Index)
{
	if (_Index < 0 || _Index > PLAYERSKILLNUM)
	{
		return;
	}

	m_IsCoolTimeReduce[_Index] = true;

}

void UPlayerSkillWidgets::SetCoolTimeReduce2(int32 _Index, float _DeltaTime)
{
	if (_Index < 0 || _Index > PLAYERSKILLNUM)
	{
		return;
	}

	float Time = m_PlayerSkillWidgetArray[_Index]->GetCurrentCoolTime();

	m_SkillCoolTimePercent[_Index] = m_PlayerSkillWidgetArray[_Index]->GetSkillCoolTimeRatio();

	m_PlayerSkillWidgetArray[_Index]->SetCurrentCoolTime(Time);
}



void UPlayerSkillWidgets::InitiallizeSkillWidget()
{
	for (int i = 0; i < PLAYERSKILLNUM; ++i)
	{
		const FString str = FString::Printf(TEXT("WBP_PlayerSkillWidget_%d"), i);
		FName WidgetName = *str;
		m_PlayerSkillWidgetArray.Add(Cast<UPlayerSkillWidget>(this->GetWidgetFromName(WidgetName)));
		m_PlayerSkillWidgetArray[i]->SetPlayerSkill(SkillNamesMap[i]);
		m_SkillCoolTimePercent[i] = m_PlayerSkillWidgetArray[i]->GetSkillCoolTimeRatio();
	}
	int a = 0;
}

void UPlayerSkillWidgets::InitiallizePlayerSkillName()
{
	for (int32 i = 0; i < PLAYERSKILLNUM; i++)
	{
		SkillNamesMap.Add(TTuple<int32, FName>(i, SkillNamesArray[i]));
	}


}
