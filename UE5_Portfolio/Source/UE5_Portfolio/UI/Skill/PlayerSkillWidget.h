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
	
	void SetPlayerSkill(FName _Name);
	void BindProgressBar(class UPlayerSkillWidgets* _PlayerSkillWidgets);
	void UpDataSkillCoolTime();

	UFUNCTION(BlueprintCallable)
	float SkillCoolTimeDown();

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetSkillCoolTimeRatio()
	{
		return ((float)m_CurrentCoolTime / (float)m_MaxCoolTime);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UProgressBar* GetProgressBar()
	{
		return m_ProgressBar;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetMaxCoolTime()
	{
		return m_MaxCoolTime;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetCurrentCoolTime()
	{
		return m_CurrentCoolTime;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentCoolTime(int32 _Value)
	{
		m_CurrentCoolTime = _Value;
	}

	

private:
	
	UProgressBar* m_ProgressBar;

	class UImage* m_SkillIcon = nullptr;

	class UTextBlock* m_CoolTimeTextBlock = nullptr;

	FName m_SkillName = FName("None");

	FString m_SkillCoolTime;

	int32 m_MaxCoolTime;

	int32 m_CurrentCoolTime;

	float m_CoolTimeRatio;

	bool m_CoolTimeReduce = false; 
private:

	class UPlayerSkillWidgets* m_PlayerSkillWidgets = nullptr;

	struct FPlayerSkillData* m_PlayerSkillData = nullptr;
	
};
