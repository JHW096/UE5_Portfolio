// Fill out your copyright notice in the Description page of Project Settings.


#include "CastingBarWidget.h"
#include "Components/ProgressBar.h"

void UCastingBarWidget::NativeConstruct()
{
	m_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("CastingBar")));

	if (m_ProgressBar == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s(%u) : m_ProgressBar == Nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	m_ProgressBar->SetPercent(0.5f);
}

void UCastingBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	/*if (!IsProgressBarHidden())
	{
		m_FillAmount += InDeltaTime / 10.0f;
		if (m_FillAmount >= 100.0f)
		{
			this->Visibility = ESlateVisibility::Hidden;
		}
		m_ProgressBar->SetPercent(m_FillAmount);
	}
	else
	{
		FillReset();
	}*/

}

