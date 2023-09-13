// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillWidgetObject.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API USkillWidgetObject : public UObject
{
	GENERATED_BODY()
	
public:

	FORCEINLINE class UPlayerSkillWidget* GetPlayerSkillWidget()
	{
		return m_PlayerSkillWidget;
	}

	FORCEINLINE struct FPlayerSkillData* GetPlayerSkillData()
	{
		return m_PlayerSkillData;
	}

	FORCEINLINE void SetPlayerSkillWidget(class UPlayerSkillWidget* p_PlayerSkillWidget)
	{
		m_PlayerSkillWidget = p_PlayerSkillWidget;
	}

	FORCEINLINE void SetPlayerSkillData(struct FPlayerSkillData* p_PlayerSkillData)
	{
		m_PlayerSkillData = p_PlayerSkillData;
	}
	

private:

	class UPlayerSkillWidget* m_PlayerSkillWidget;

	struct FPlayerSkillData* m_PlayerSkillData;

};
