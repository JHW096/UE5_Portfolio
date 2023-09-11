// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"



UCLASS()
class UE5_PORTFOLIO_API UPlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void BindHp(class UPlayerStatComponent* StatComponent);
	void BindMp(class UPlayerStatComponent* StatComponent);

	void UpdateHp();
	void UpdataMp();


private:

	TWeakObjectPtr<class UPlayerStatComponent> m_CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_PlayerHpBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_PlayerMpBar;

};
