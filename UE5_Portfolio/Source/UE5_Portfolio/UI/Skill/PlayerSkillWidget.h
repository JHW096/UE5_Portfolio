// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerSkillWidget.generated.h"

/**
 * 
 */


UCLASS()
class UE5_PORTFOLIO_API UPlayerSkillWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	FORCEINLINE float GetSkillCoolTimeRatio()
	{
		return (m_PassTime / m_CoolTime);
	}
	
	FORCEINLINE float GetSkillPassingTime()
	{
		return m_PassTime;
	}

	FORCEINLINE float GetSkillCoolTime()
	{
		return m_CoolTime;
	}

	void SetSkillPassingTime(float _Time);
	
	
private:
	
	struct FPlayerSkillData* m_SkillData;
	
	UProgressBar* m_ProgressBar = nullptr;


private:

	float m_CoolTime;
	float m_PassTime;
		
};
