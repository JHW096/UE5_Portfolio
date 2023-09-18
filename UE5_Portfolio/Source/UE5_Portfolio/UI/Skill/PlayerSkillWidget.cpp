// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Progressbar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../../Player/Data/PlayerSkillData.h"
#include "../../Global/TopDownGameInstance.h"
#include "PlayerSkillWidgets.h"
#include "Kismet/KismetSystemLibrary.h"



void UPlayerSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();


	//m_CoolTimeTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("CoolTimeText")));
}

void UPlayerSkillWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}

void UPlayerSkillWidget::BindProgressBar(UPlayerSkillWidgets* _PlayerSkillWidgets)
{
	m_PlayerSkillWidgets = _PlayerSkillWidgets;
	m_PlayerSkillWidgets->OnQButtonProgress.AddUObject(this, &UPlayerSkillWidget::UpDataSkillCoolTime);
}

void UPlayerSkillWidget::SetPlayerSkill(FName _Name)
{
	UTopDownGameInstance* GameInst = Cast<UTopDownGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInst == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) GameInst == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	FPlayerSkillData* SkillData = GameInst->GetPlayerSkillData(_Name);

	if (SkillData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) SkillData== nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	m_PlayerSkillData = SkillData;
	m_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SkillProgressBar")));
	m_SkillName = m_PlayerSkillData->SkillName;
	m_MaxCoolTime = m_PlayerSkillData->SkillCoolTime;
	m_CurrentCoolTime = m_PlayerSkillData->SkillCoolTime;
}



void UPlayerSkillWidget::UpDataSkillCoolTime()
{
	m_ProgressBar->SetPercent(GetSkillCoolTimeRatio());
}

void UPlayerSkillWidget::CoolTimeReduce(float _DeltaTime)
{
	m_CurrentCoolTime = m_CurrentCoolTime - ((1.0f) * _DeltaTime);
}

float UPlayerSkillWidget::SkillCoolTimeDown()
{
	return GetSkillCoolTimeRatio();
}





