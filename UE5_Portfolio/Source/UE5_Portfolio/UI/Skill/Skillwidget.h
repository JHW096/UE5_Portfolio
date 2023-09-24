// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skillwidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API USkillwidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:


	UFUNCTION(BlueprintCallable)
	float GetRatio()
	{
		return m_CoolDownValue / m_CoolTime;
	}

	void SetCoolDownValue(float _Value)
	{
		m_CoolDownValue = _Value;
	}


private:

	float m_CoolTime = 10.0f;

	float m_CoolDownValue = 10.0f;

	float m_Ratio;


	
};
