// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSkillTileViewWidget.generated.h"

/**
 * 
 */

UCLASS()
class UE5_PORTFOLIO_API UPlayerSkillTileViewWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	void SetSkillWidgetProgressBarPercent(size_t _Value);

	class UPlayerSkillWidget* GetPlayerSkillWidgetFromTileView(size_t _Value);

private:

	void SetTableRowName();
	FName GetTableRowName(int _Key);
	class UPlayerSkillWidget* CreateSkillWidget(FName _Name);
	class USkillWidgetObject* CreateSkillWidgetObject(FName _Name);

private: 

	const int32 PLAYER_SKILL_SIZE = 4;

	UPROPERTY(Category = "InvenList", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTileView* m_SkillList = nullptr;

	TArray<class UPlayerSkillWidget*> m_SkillWidgetList;

	TMap<int, FName> TableRowNameMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPlayerSkillWidget> TSkillWidget;
};
