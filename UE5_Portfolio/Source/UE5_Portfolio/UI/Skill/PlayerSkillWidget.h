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

	virtual void NativeOnInitialized() override;
	
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	void PlayerSkillWidgetSetting(struct FPlayerSkillData* _PlayerSkillData);
	
public:

	FORCEINLINE float GetSkillCoolTimeRatio()
	{
		return ((float)m_CurrentCoolTime / (float)m_MaxCoolTime);
	}

	FORCEINLINE class UProgressBar* GetProgressBar()
	{
		return m_ProgressBar;
	}

	FORCEINLINE int32 GetMaxCoolTime()
	{
		return m_MaxCoolTime;
	}

	void SetProgressBar();

private:

	class UProgressBar* m_ProgressBar;

	class UImage* m_SkillIcon = nullptr;

	class UTextBlock* m_CoolTimeTextBlock = nullptr;

	FName m_SkillName = FName("None");

	FString m_SkillCoolTime;

	int32 m_MaxCoolTime;

	int32 m_CurrentCoolTime;

	float m_CoolTimeRatio;
	

private:

	struct FPlayerSkillData* m_PlayerSkillData = nullptr;
	
};
