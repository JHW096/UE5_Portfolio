// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void BindHp(class UMonsterStatComponent* StatComp);
			
	void UpdateHp();

private:

	TWeakObjectPtr<class UMonsterStatComponent> m_CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;
};
