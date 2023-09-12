// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Progressbar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../../Player/Data/PlayerSkillData.h"
#include "../../Global/TopDownGameInstance.h"

void UPlayerSkillWidget::NativeConstruct()
{
	m_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SkillProgressBar")));
	m_CoolTimeTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("CoolTimeText")));

	if (m_PlayerSkillData == nullptr || m_ProgressBar == nullptr || m_CoolTimeTextBlock == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) : No PlayerSkillUI Settings"), __FUNCTION__, __LINE__);
		return;
	}
}

void UPlayerSkillWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UPlayerSkillWidget::PlayerSkillWidgetSetting(FPlayerSkillData* _PlayerSkillData)
{
	FSlateBrush BackGroundBrush = UWidgetBlueprintLibrary::MakeBrushFromTexture(_PlayerSkillData->SkillIcon, 50, 50);

	m_ProgressBar->WidgetStyle.BackgroundImage = BackGroundBrush;
	m_SkillName = _PlayerSkillData->SkillName;
	m_MaxCoolTime = _PlayerSkillData->SkillCoolTime;
}


