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

	/*
	
	UNCTION(BlueprintCallable)
	FORCEINLINE bool IsProgressBarHidden()
	{
		return this->Visibility == ESlateVisibility::Hidden ? true : false;
	}

	FORCEINLINE void TurnOnProgressbar()
	{
		this->Visibility == ESlateVisibility::Visible;
	}*/

	/*FORCEINLINE void TurnOffProgressbar()
	{
		this->Visibility = ESlateVisibility::Hidden;
	}*/

	FORCEINLINE class UProgressBar* GetProgressBar()
	{
		return m_ProgressBar;
	}

	FORCEINLINE void FillReset()
	{
		m_FillAmount = 0.0f;
	}

	FORCEINLINE float GetFillAmount()
	{
		return m_FillAmount;
	}

public:

	UFUNCTION(BlueprintCallable)
	float FillProgressBar();

private:

	class UProgressBar* m_ProgressBar = nullptr;

	UPROPERTY(Category = "value", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_FillAmount = 0.0f;

	UPROPERTY(Category = "value", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_FillSpeed = 0.5f;
};
