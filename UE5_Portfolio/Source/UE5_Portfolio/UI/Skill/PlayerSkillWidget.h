// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	void PlayerSkillWidgetSetting(struct FPlayerSkillData* _PlayerSkillData);
	
public:

	FORCEINLINE float GetSkillCoolTimeRatio()
	{
		return ((float)m_CurrentCoolTime / (float)m_MaxCoolTime);
	}

private:

	class UProgressBar* m_ProgressBar = nullptr;

	class UImage* m_SkillIcon = nullptr;

	class UTextBlock* m_CoolTimeTextBlock = nullptr;

	FName m_SkillName;

	FString m_SkillCoolTime;

	int32 m_MaxCoolTime;

	int32 m_CurrentCoolTime;

	float m_CoolTimeRatio;
	

private:

	struct FPlayerSkillData* m_PlayerSkillData = nullptr;
	
};
