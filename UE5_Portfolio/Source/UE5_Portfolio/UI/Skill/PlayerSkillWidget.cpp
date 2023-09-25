// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Progressbar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../../Player/Data/PlayerSkillData.h"
#include "../../Global/TopDownGameInstance.h"
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

void UPlayerSkillWidget::SetSkillPassingTime(float _Time)
{
	m_PassTime = _Time;
}

