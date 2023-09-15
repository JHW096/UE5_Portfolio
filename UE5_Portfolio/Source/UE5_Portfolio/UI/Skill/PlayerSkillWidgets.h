// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSkillWidgets.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UPlayerSkillWidgets : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	
	class UPlayerSkillWidget* GetPlayerWidgetElement(size_t _index);
	void SetPlayerWidgetElement(size_t _index, FName _Name);

	void FillAmountFullElement(int32 _index);

private:

	void InitiallizeSkillWidget();
	void InitiallizePlayerSkillName();

private:

	const int32 PLAYERSKILLNUM = 4;
	const TArray<FName> SkillNamesArray = { "None", "None", "None", "SnipeShot" };

	TMap<int32, FName> SkillNamesMap;

	UPROPERTY()
	TArray<class UPlayerSkillWidget*> m_PlayerSkillWidgetArray;

};
