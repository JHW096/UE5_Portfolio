// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Progressbar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../../Player/Data/PlayerSkillData.h"
#include "../../Global/TopDownGameInstance.h"

void UPlayerSkillWidget::NativeOnInitialized()
{
	int a = 0;
	//m_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SkillProgressBar")));
}

void UPlayerSkillWidget::NativePreConstruct()
{
	//m_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SkillProgressBar")));
}

void UPlayerSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SkillProgressBar")));
	m_CoolTimeTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("CoolTimeText")));

	int a = 0;

	if (m_PlayerSkillData == nullptr || m_ProgressBar == nullptr || m_CoolTimeTextBlock == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) : No PlayerSkillUI Settings"), __FUNCTION__, __LINE__);
		return;
	}
}

void UPlayerSkillWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPlayerSkillWidget::PlayerSkillWidgetSetting(FPlayerSkillData* _PlayerSkillData)
{
	/*FSlateBrush BackGroundBrush = UWidgetBlueprintLibrary::MakeBrushFromTexture(_PlayerSkillData->SkillIcon, 50, 50);

	m_ProgressBar->WidgetStyle.BackgroundImage = BackGroundBrush;*/
	
	m_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SkillProgressBar")));
	m_PlayerSkillData = _PlayerSkillData;
	m_SkillName = _PlayerSkillData->SkillName;
	m_MaxCoolTime = _PlayerSkillData->SkillCoolTime;
}

void UPlayerSkillWidget::SetProgressBar()
{
	m_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SkillProgressBar")));
}


