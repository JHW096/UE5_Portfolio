// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CastingBarWidget.generated.h"

/**
 * void UItemSlot::NativeConstruct()
 */
UCLASS()
class UE5_PORTFOLIO_API UCastingBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	FORCEINLINE bool IsProgressBarHidden()
	{
		return this->Visibility == ESlateVisibility::Hidden ? true : false;
	}

	FORCEINLINE class UProgressBar* GetProgressBar()
	{
		return m_ProgressBar;
	}

	FORCEINLINE void FillReset()
	{
		m_FillAmount = 0.0f;
	}

public:


private:

	class UProgressBar* m_ProgressBar = nullptr;

	float m_FillAmount = 0.0f;
};
